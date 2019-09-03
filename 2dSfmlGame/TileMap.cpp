#include "TileMap.h"
#include "Utils.h"


TileMap::TileMap() {


}

TileMap::~TileMap() {
	rm = nullptr;
	pTiledata = nullptr;
}


void TileMap::Init(ResourceManager* r)
{
	rm = r;
}

bool TileMap::LoadFromCache(const std::string& texturePath) {
	// load the tileset texture
	if (rm->GetTexture(texturePath, _tileset)) {
		DBOUT("Failed to load texture: " << texturePath);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool TileMap::load(const std::string& texturePath, sf::Vector2u tileSize,  int* tiles, unsigned int width, unsigned int height)
{
	// load the tileset texture
	if (LoadFromCache(texturePath)) {
		return EXIT_FAILURE;
	}

	//Digest level data
	SizeOfTileTexturesPixels = tileSize;
	TilesInLevel = sf::Vector2u(width, height);
	LevelDimensions = sf::Vector2u(width*tileSize.x, height*tileSize.y);
	NumberOfTilesInTexture = sf::Uint32((_tileset->getSize().x / tileSize.x)*(_tileset->getSize().y / tileSize.y));

	
	// resize the vertex array to fit the level size
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile varient
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (_tileset->getSize().x / tileSize.x);
			int tv = tileNumber / (_tileset->getSize().y / tileSize.y);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &_vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

		}
	
	


	return EXIT_SUCCESS;
}

bool TileMap::load(LevelTileData& ld) 
{
	pTiledata = &ld;
	return load(ld.tilesetFilepath, ld.tileSize, ld.tiles, ld.leveldim.x, ld.leveldim.y);
}



sf::Vector2i TileMap::changeTile(sf::Vector2f position, sf::Uint32 newTileTex) {
	//compare position against tilemap bounds
	//	if inside level
	//		find which tile position is over
	//		get quad for that tile
	//		change quad texcoords to new texture from tile texture

	if((position.x > getPosition().x) && (position.x < getPosition().x + LevelDimensions.x))
		if ((position.y > getPosition().y) && (position.y < getPosition().y + LevelDimensions.y)) {
			//inside level
			sf::Vector2f temppos = position - getPosition();
			int Tilex =  (int(temppos.x) / SizeOfTileTexturesPixels.x);
			int Tiley =  (int(temppos.y) / SizeOfTileTexturesPixels.y);
			//get quad
			sf::Vertex* quad = &_vertices[(Tilex + Tiley * TilesInLevel.x) * 4];

			int tu = newTileTex % (_tileset->getSize().x / SizeOfTileTexturesPixels.x);
			int tv = newTileTex / (_tileset->getSize().y / SizeOfTileTexturesPixels.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * SizeOfTileTexturesPixels.x, tv * SizeOfTileTexturesPixels.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * SizeOfTileTexturesPixels.x, tv * SizeOfTileTexturesPixels.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * SizeOfTileTexturesPixels.x, (tv + 1) * SizeOfTileTexturesPixels.y);
			quad[3].texCoords = sf::Vector2f(tu * SizeOfTileTexturesPixels.x, (tv + 1) * SizeOfTileTexturesPixels.y);


			return sf::Vector2i(Tilex, Tiley);
		}
	return sf::Vector2i(-1,-1);
}

sf::Vector2i TileMap::getTileFromPosition(sf::Vector2f worldPos)
{
	if ((worldPos.x > getPosition().x) && (worldPos.x < getPosition().x + LevelDimensions.x))
		if ((worldPos.y > getPosition().y) && (worldPos.y < getPosition().y + LevelDimensions.y)) {
			//inside level
			sf::Vector2f temppos = worldPos - getPosition();
			int Tilex = (int(temppos.x) / SizeOfTileTexturesPixels.x);
			int Tiley = (int(temppos.y) / SizeOfTileTexturesPixels.y);
			return sf::Vector2i(Tilex, Tiley);
		}
	//outside level
	return sf::Vector2i(-1,-1);
}

sf::Vector2f TileMap::getPositionFromTile(sf::Vector2i tileNum)
{
	sf::Vector2f resultpos;
	if(tileNum.x >= 0 && tileNum.y >= 0)
		if (tileNum.x < TilesInLevel.x && tileNum.y < TilesInLevel.y) {
			//inside level bounds
			resultpos = getPosition() + sf::Vector2f(tileNum.x *pTiledata->tileSize.x, tileNum.y * pTiledata->tileSize.y);
		}

	return resultpos;
}

//Generate new map
bool TileMap::GenerateMap(LevelTileData& levelToGen) {
	//levelToGen is owned by GameLevel object
	//	it contains data related to GameLevel::_currentLevelData and GameLevel::_tileset
	pTiledata = &levelToGen;
	
	//	load texture to use
	if (LoadFromCache(pTiledata->tilesetFilepath))
		return EXIT_FAILURE;

	//	use texture data to determine possible tile values
	int numberTilesInTexturex	(_tileset->getSize().x / pTiledata->tileSize.x);
	int numberTilesInTexturey	(_tileset->getSize().y / pTiledata->tileSize.y);

	//	use data in LevelTileData to fill *tiles field
	//	then use data to create vertex array
	GenerateTiles (numberTilesInTexturex, numberTilesInTexturey, pTiledata->tiles, pTiledata->leveldim.x, pTiledata->leveldim.y);

	

	

	return EXIT_SUCCESS;
}

void TileMap::GenerateTiles(int tilesInTexturex, int tilesInTexturey, int *&tiles, unsigned int width, unsigned int height) {

	TilesInLevel = sf::Vector2u(width, height);
	LevelDimensions = sf::Vector2u(width*pTiledata->tileSize.x, height*pTiledata->tileSize.y);

	//new *tiles[] array
	if (tiles != nullptr)
		delete[] tiles;
	tiles = new int[width*height];

	//now loop through and randomly assign features
	int doubleRange(tilesInTexturex * tilesInTexturey*2);

	int count(0);
	for (int i(0);i<width;++i)
		for (int j(0); j < height; ++j)
		{
			int val = rand() % doubleRange;
			val -= doubleRange / 2;	//val between: -range -> range
			//modify divide to modify chance of doodad appearing
			DBOUT("random value for Doodad: " << val);

			if (val >= 0) {
				//add doodad
				tiles[i + j * width] = val;
				count++;
			}
			else {	//, or leave blank (-1 is blank)
				tiles[i + j * width] = -1;
			}
		}
		//	choose random values from tilesInTexture

		//now create vertices
		_vertices.setPrimitiveType(sf::Quads);
		_vertices.resize(count * 4);

		//get tilesize from texture data
		sf::Vector2u tempTilesize(pTiledata->tileSize);

		int vertexCounter(0);
		// populate the vertex array. loop through tiles array and only add if doodad is present
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile varient
				int tileNumber = tiles[i + j * width];
				if (tileNumber != -1) {//skip tile if it's empty
					// find its position in the tileset texture
					int tu = tileNumber % (_tileset->getSize().x / tempTilesize.x);
					int tv = tileNumber / (_tileset->getSize().y / tempTilesize.y);

					// get a pointer to the current tile's quad
					//	_vertices is smaller than tiles array
					sf::Vertex* quad = &_vertices[(vertexCounter) * 4];

					// define its 4 corners
					quad[0].position = sf::Vector2f(i * tempTilesize.x, j * tempTilesize.y);
					quad[1].position = sf::Vector2f((i + 1) * tempTilesize.x, j * tempTilesize.y);
					quad[2].position = sf::Vector2f((i + 1) * tempTilesize.x, (j + 1) * tempTilesize.y);
					quad[3].position = sf::Vector2f(i * tempTilesize.x, (j + 1) * tempTilesize.y);

					// define its 4 texture coordinates
					quad[0].texCoords = sf::Vector2f(tu * tempTilesize.x, tv * tempTilesize.y);
					quad[1].texCoords = sf::Vector2f((tu + 1) * tempTilesize.x, tv * tempTilesize.y);
					quad[2].texCoords = sf::Vector2f((tu + 1) * tempTilesize.x, (tv + 1) * tempTilesize.y);
					quad[3].texCoords = sf::Vector2f(tu * tempTilesize.x, (tv + 1) * tempTilesize.y);
					vertexCounter++;
				}
			}
		
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &(*_tileset);//Dereference shared_ptr, then pass texture to renderStates

	// draw the vertex array
	target.draw(_vertices, states);
}

//Tilemap Helpers
sf::Vector2u TileMap::getLevelSize() {
	return LevelDimensions;
}

int TileMap::getNumTiles() {
	return NumberOfTilesInTexture;
}
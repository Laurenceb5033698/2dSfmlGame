#include "TileMap.h"
#include "Utils.h"


bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset)) {
		DBOUT("Failed to load texture: " << tileset);
		return EXIT_FAILURE;
	}
	SizeOfTileTexturesPixels = tileSize;
	TilesInLevel = sf::Vector2u(width, height);
	LevelDimensions = sf::Vector2u(width*tileSize.x, height*tileSize.y);
	NumberOfTilesInTexture = sf::Uint32((m_tileset.getSize().x / tileSize.x)*(m_tileset.getSize().y / tileSize.y));
	
	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile varient
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().y / tileSize.y);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

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
	//offset level, move to centre middle of level to origin
	setPosition(	float(LevelDimensions.x) /-2,
					float(LevelDimensions.y) /-2 );


	return EXIT_SUCCESS;
}

void TileMap::changeTile(sf::Vector2f position, sf::Uint32 newTileTex) {
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
			sf::Vertex* quad = &m_vertices[(Tilex + Tiley * TilesInLevel.x) * 4];

			int tu = newTileTex % (m_tileset.getSize().x / SizeOfTileTexturesPixels.x);
			int tv = newTileTex / (m_tileset.getSize().y / SizeOfTileTexturesPixels.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * SizeOfTileTexturesPixels.x, tv * SizeOfTileTexturesPixels.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * SizeOfTileTexturesPixels.x, tv * SizeOfTileTexturesPixels.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * SizeOfTileTexturesPixels.x, (tv + 1) * SizeOfTileTexturesPixels.y);
			quad[3].texCoords = sf::Vector2f(tu * SizeOfTileTexturesPixels.x, (tv + 1) * SizeOfTileTexturesPixels.y);

		}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}
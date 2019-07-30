#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"



class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	~TileMap();

	sf::Vector2u getLevelSize();
	int getNumTiles();


	struct LevelTileData {
		std::string tilesetFilepath;	//filepath of texture
		//sf::Vector2u tilesInTexture;	//texture dimesions in tiles
		sf::Vector2u tileSize;	//tile size in pixels
		sf::Vector2u leveldim;	//level dimensions in tiles
		int* tiles;		//*array of tiles data
		LevelTileData()
			:tilesetFilepath(""), tileSize(0,0), tiles(nullptr), leveldim(0,0)
		{}
		LevelTileData(std::string filepath, unsigned int tilePxWidth, unsigned int tilePxHeight, int* tileData, unsigned int levelWidth, unsigned int levelHeight)
			:tilesetFilepath(filepath), tileSize(tilePxWidth, tilePxHeight), tiles(tileData), leveldim(levelWidth, levelHeight)
		{ }
		LevelTileData(std::string filepath, int tilePxWidth, int tilePxHeight, int* tileData, int levelWidth, int levelHeight)
			:tilesetFilepath(filepath), tileSize(tilePxWidth, tilePxHeight), tiles(tileData), leveldim(levelWidth, levelHeight)
		{ }

		LevelTileData(const LevelTileData&) = delete;	//Explicitly disallow copying (would delete *tiles[])

		~LevelTileData()
		{
			delete[] tiles;
		}
		void SetData(std::string filepath, unsigned int tilePxWidth, unsigned int tilePxHeight, int* tileData, unsigned int levelWidth, unsigned int levelHeight)
		{
			tilesetFilepath = filepath;
			tileSize = sf::Vector2u(tilePxWidth, tilePxHeight);
			tiles = tileData;
			leveldim = sf::Vector2u(levelWidth, levelHeight);
		}
	private:
	};

	void Init(ResourceManager* r);

	void setTileData(const std::string& tileset, sf::Vector2u tileSize, int* tiles, unsigned int width, unsigned int height);
	//Load asset and initialise required rendering data
	//Returns TRUE if Loading FAILS
	bool LoadFromCache(const std::string& texturePath);

	bool load(const std::string& tileset, sf::Vector2u tileSize, int* tiles, unsigned int width, unsigned int height);
	bool load(LevelTileData& levelData);

	//generates tiles, and fills vertexarray
	bool GenerateMap(LevelTileData& levelToGenerate);
	//fills *tiles with values
	void GenerateTiles(int TileInTexturex, int TilesInTexturey, int* &tiles, unsigned int width, unsigned int height);

	sf::Vector2i changeTile(sf::Vector2f posistion, sf::Uint32 newTileTex);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	ResourceManager* rm;

	//level/texture data: owned by GameLevel
	LevelTileData * pTiledata ;	

	sf::Vector2u SizeOfTileTexturesPixels;//dimension of texture in pixels
	sf::Vector2u LevelDimensions;		//dimensions of level in pixels
	sf::Vector2u TilesInLevel;			//dimension of level in tiles
	sf::Uint32 NumberOfTilesInTexture;	//number of tiles in texture

	sf::VertexArray _vertices;
	std::shared_ptr<sf::Texture> _tileset;
};
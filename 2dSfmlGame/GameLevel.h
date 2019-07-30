#pragma once
#include "TileMap.h"

//Gamelevel holds the tilemap and controls what tileset and level data to load
//	could also hold several tilesets
//	could also hold several tilemaps, and render all together/ stitched
//	
class GameLevel
{
public:
	GameLevel();
	~GameLevel();
	
	//load level(int)
	void Init(ResourceManager* r);
	bool LoadTilemap(std::string filepath);

	void changeTile(sf::Vector2f pos, unsigned int newTileType);
	void Draw(sf::RenderWindow& rwind);

	sf::Vector2f getCentre();
	int getNumTiles();

private:

	bool readLevelData(std::string levelFilePath, TileMap::LevelTileData& data);
	TileMap _tileMap;
	TileMap _doodads;

	TileMap::LevelTileData _currentLevelData;
	TileMap::LevelTileData _currentDoodadData;

};


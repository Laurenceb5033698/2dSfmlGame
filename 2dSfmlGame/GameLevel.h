#pragma once
#include "TileMap.h"
#include "Sprite.h"
#include "Trees.h"
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
	bool LoadResources();

	void changeTile(sf::Vector2f pos, unsigned int newTileType);
	void Update(float dt);
	void Draw(sf::RenderWindow& rwind);

	sf::Vector2f getCentre();
	int getNumTiles();

	void addTree(sf::Vector2i tile);

	bool testTile(sf::Vector2i tile);
	void setGridTile(sf::Vector2i tile);
private:
	ResourceManager* rm;
	bool readLevelData(std::string levelFilePath, TileMap::LevelTileData& data);
	void createGridData();
	TileMap _tileMap;

	TileMap::LevelTileData _currentLevelData;

	int * _GridData;//for collisions
	std::vector<Trees> _Trees;


};


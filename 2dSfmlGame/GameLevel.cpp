#include "GameLevel.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//max size of level buffer
#define MAX_BUFFER 1024


GameLevel::GameLevel()
{
}


GameLevel::~GameLevel()
{
}

void GameLevel::Init(ResourceManager* r) 
{
	_tileMap.Init(r);
	_doodads.Init(r);

}




void GameLevel::Draw(sf::RenderWindow& rWind) 
{
	rWind.draw(_tileMap);
	rWind.draw(_doodads);

}

bool GameLevel::readLevelData(std::string levelFilePath, TileMap::LevelTileData& data)
{
	int levelx(0), levely(0), tilex(0), tiley(0);
	std::string texturefilepath;
	int* levelData = nullptr;
	//open file
	std::string line,str;
	std::stringstream ss;
	std::ifstream file(levelFilePath);
	if (!file.is_open()) {
		DBOUT("Could not open level Data file! :" << levelFilePath);
		return EXIT_FAILURE;
	}
	else
	{
		//read level size dimensions
		getline(file, line);
		ss.str(line);
		ss >> levelx >> levely;
		ss.clear();
		//read tile pixel dimensions
		getline(file, line);
		ss.str(line);
		ss >> tilex >> tiley;

		//read tilesetFilepath
		getline(file, line);
		texturefilepath = line;

		//read tile data
		size_t levelBufferLength = levelx * levely;
		if (levelBufferLength > MAX_BUFFER) {
			DBOUT("LevelData Buffer too large!: " << levelBufferLength << ". Max buffer: " << MAX_BUFFER);
			return EXIT_FAILURE;
		}

		//read data
		levelData = new int[levelBufferLength];
		int i(0);
		while (i < levelBufferLength && file >> levelData[i]) {
			++i;
		}
		//store data
		data.SetData(texturefilepath, tilex, tiley, levelData, levelx, levely);
		
	}

	return EXIT_SUCCESS;
}

void GameLevel::changeTile(sf::Vector2f pos, unsigned int newTileType)
{
	sf::Vector2i resultTile = _tileMap.changeTile(pos, newTileType);
	if(resultTile.x != -1 && resultTile.y != -1){
		//Tile changed is valid
		//change tile data
		int oldTile = _currentLevelData.tiles[resultTile.x + (resultTile.y * _currentLevelData.leveldim.x)];
		_currentLevelData.tiles[resultTile.x + (resultTile.y * _currentLevelData.leveldim.x)] = newTileType;
		DBOUT("Tile Changed: Old Tile = " << oldTile << " new Tile = " << newTileType);
	}
}

bool GameLevel::LoadTilemap(std::string filepath) 
{
	if (readLevelData(filepath, _currentLevelData)) {
		DBOUT("Failed to load leveldata from file");
		return EXIT_FAILURE;
	}
	if (_tileMap.load(_currentLevelData))
	{
		DBOUT("Failed to load tilemap from leveldata");
		return EXIT_FAILURE;
	}
	//make levelDoodad data
	_currentDoodadData.SetData("resources/sprites/Doodads_less.png",64,64,nullptr,_currentLevelData.leveldim.x,_currentLevelData.leveldim.y);
	//Doodad data is based on _currentlevel dimensions, but uses a different tileset and generates doodads by seed.
	if(_doodads.GenerateMap(_currentDoodadData))
	{
		DBOUT("Failed to load doodads.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

//Helpers
sf::Vector2f GameLevel::getCentre() {
	sf::Vector2f pos(_tileMap.getPosition());
	pos.x += _tileMap.getLevelSize().x / 2;
	pos.y += _tileMap.getLevelSize().y / 2;

	return pos;
}

int GameLevel::getNumTiles()
{
	return _tileMap.getNumTiles();
}


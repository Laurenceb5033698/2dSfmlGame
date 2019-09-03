#include "GameLevel.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//max size of level buffer
#define MAX_BUFFER 1024


GameLevel::GameLevel()
	:_GridData(NULL)
{
}


GameLevel::~GameLevel()
{
	_Trees.clear();
	if (_GridData != NULL)
		delete[] _GridData;
}

void GameLevel::Init(ResourceManager* r) 
{
	rm = r;
	_tileMap.Init(r);
	

}

void GameLevel::Update(float dt) 
{
	for (int i(0); i < _Trees.size(); ++i) {
		_Trees.at(i).Update(dt);
	}
}



void GameLevel::Draw(sf::RenderWindow& rWind) 
{
	rWind.draw(_tileMap);
	for (int i(0); i < _Trees.size(); ++i) {
		rWind.draw(_Trees.at(i));
	}

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
	//create collision grid data based on level size
	createGridData();
	
	return EXIT_SUCCESS;
}

void GameLevel::createGridData() 
{
	if (_GridData != NULL)
		delete[] _GridData;
	size_t levelBufferLength = _currentLevelData.leveldim.x * _currentLevelData.leveldim.y;
	_GridData = new int[levelBufferLength]();	//initialized with 0s
	//if impassable terrain in level, add to _gridData as 1s
}

	//Load all the icons that are used on the map
bool GameLevel::LoadResources() 
{	
	//count if any failed to load
	int failed = 0;
	//add any true value to the failed count
	failed += rm->LoadTexture("resources/sprites/trees2.png");
	

	return failed > 0;	//if any failed, then return true
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

//
void GameLevel::addTree(sf::Vector2i tile)
{
	//create Sprite
	Trees aTree;
	//init sprite
	aTree.Init(rm);
	//load sprite texture
	if (aTree.Load("resources/sprites/trees2.png")) {
	//	failed to load texture
	//	do not add sprite
		return;
	}
	//else
	//if success
	//	position object
	//	get tile
	
	//test tile against grid
	if (testTile(tile))
	{
		setGridTile(tile);
		aTree.setPosition(_tileMap.getPositionFromTile(tile));

		//	add to list
		_Trees.push_back(aTree);
		DBOUT("Tree added");
		return;
	}
	DBOUT("Failed to add tree");
}

bool GameLevel::testTile(sf::Vector2i mytile)
{

	//is mytile inside bounds

	//test vs grid
	if ( !_GridData[mytile.x + mytile.y *_currentLevelData.leveldim.x])
		return true;	//a 0 in _gridData is a free spot

	return false;
}

void GameLevel::setGridTile(sf::Vector2i mytile)
{
	//is mytile inside bounds
	//set grid
	_GridData[mytile.x + mytile.y *_currentLevelData.leveldim.x] = 1;
}




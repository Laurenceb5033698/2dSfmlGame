#pragma once
#include "ResourceManager.h"
#include "GameLevel.h"

#include "Stockpile.h"
//multiple teams
//they fight each other
//each has 
//	a resource pile
//	a dymanic buildings list
//	a dynamic units list

//the team is controlled by the player or an AI
class Team
{
public:
	Team();
	~Team();

	void Init(ResourceManager* r, GameLevel* gl);
	bool Load();
	bool LoadResources();

	void Update(float dt);
	void updateBuildings();
	void updateUnits();

	void placeBuilding();
	void addBuilding();

	void addStock( int val);
	void removeStock(int val); //(checks amount before remove)
	//get stock amounts



	//references
	ResourceManager* rm;
	GameLevel* p_level;

	//data

	Stockpile m_stockpile;

	//units<sprite>

	//buildings<building>

};


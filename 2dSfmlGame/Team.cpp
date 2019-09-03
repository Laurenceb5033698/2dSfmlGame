#include "Team.h"



Team::Team()
{
}


Team::~Team()
{
}

void Team::Init(ResourceManager* r, GameLevel* gl) {
	rm = r;
	p_level = gl;
}

bool Team::Load()
{
	return false;
}

bool Team::LoadResources()
{
	return false;
}

void Team::Update(float dt)
{
}

void Team::updateBuildings()
{
}

void Team::updateUnits()
{
}

void Team::placeBuilding()
{
}

void Team::addBuilding()
{
}

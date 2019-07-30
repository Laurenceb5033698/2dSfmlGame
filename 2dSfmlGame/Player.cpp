#include "Player.h"
#include "sfVectorMath.h"


Player::Player()
	:pGameLevel(nullptr), range(100), terrainType(0)
{
}


Player::~Player()
{
}

void Player::Init(ResourceManager* r, GameLevel* g) {
	MoveableEntity::Init(r);
	pGameLevel = g;
	range = 100;
}

void Player::Action(sf::Vector2f levelPos) {
	//determine what action to take (user input decides, e.g. from UI menu, or from scroll wheel)
	if (InRange(levelPos)) {
		//Build thing at target
		Terraform(levelPos);
		//destroy target building
		//upgrade target building
		//harvest target resource
		//try interact with target using tool
	}
}

void Player::Build(sf::Vector2f levelPos) {
	//determine what to build (e.g. house, lumbercamp, barracks etc)

}

void Player::Terraform(sf::Vector2f levelPos) {
	//changeGroundType eg "build" roads
	pGameLevel->changeTile(levelPos, terrainType);

}



//Helpers
bool Player::InRange(const sf::Vector2f& levelPos) {

	return sfm::length<float>(levelPos - getPosition()) <= range;
}

void Player::setTerrainType(int typ) {
	if(typ >=0)
		terrainType = typ;
}

void Player::nextTerrainType(int inc)
{
	if(terrainType+inc >= 0 && terrainType+inc < pGameLevel->getNumTiles() )
		terrainType += inc;
}


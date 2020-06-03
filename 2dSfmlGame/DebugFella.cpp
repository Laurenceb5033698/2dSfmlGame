#include "DebugFella.h"
#include "sfVectorMath.h"


DebugFella::DebugFella()
	:pGameLevel(nullptr), range(100), terrainType(0), direction(0), sprinting(false), sprintSpeed(240)
{
}


DebugFella::~DebugFella()
{
}

void DebugFella::Init(ResourceManager* r, GameLevel* g) {
	AnimatedSprite::Init(r);
	pGameLevel = g;
	range = 100;
}

void DebugFella::Action(sf::Vector2f levelPos) {
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

void DebugFella::Build(sf::Vector2f levelPos) {
	//determine what to build (e.g. house, lumbercamp, barracks etc)

}

void DebugFella::Terraform(sf::Vector2f levelPos) {
	//changeGroundType eg "build" roads
	pGameLevel->changeTile(levelPos, terrainType);

}

void DebugFella::Movement(float deltaTime) {
	sf::Vector2f velocity(GetVelocity());
	float mag(sfm::length(velocity));
	if (mag > 0) {
		velocity /= mag;//normalize
		move(velocity * deltaTime * (sprinting?sprintSpeed:GetSpeed()) );
	}
	
}


void DebugFella::Update(float deltaTime)
{
	Movement(deltaTime);

	Animate(deltaTime);
}


void DebugFella::Animate(float deltaTime)
{
	sf::Vector2f velocity(GetVelocity());
	int prev_direction = direction;
	if (velocity.x != 0 || velocity.y != 0) {	//if movement

		//down =0, right=1, up = 2, left = 3
		if (velocity.y == 0)
			direction = ( (velocity.x > 0) ? IDLE_EAST : IDLE_WEST);
		if (velocity.x == 0)
			direction =( (velocity.y > 0) ? WALKING_SOUTH : IDLE_NORTH);

	}
	else {	//stopped moving
		if(direction == WALKING_SOUTH)
			direction = IDLE_SOUTH;
	}

	

	SetCurrentAnimation(direction, prev_direction != direction);

	AnimatedSprite::Animate(deltaTime);
}

//Helpers
bool DebugFella::InRange(const sf::Vector2f& levelPos) {

	return sfm::length<float>(levelPos - getPosition()) <= range;
}

void DebugFella::setTerrainType(int typ) {
	if(typ >=0)
		terrainType = typ;
}

void DebugFella::nextTerrainType(int inc)
{
	if(terrainType+inc >= 0 && terrainType+inc < pGameLevel->getNumTiles() )
		terrainType += inc;
}


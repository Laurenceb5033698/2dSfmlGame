#pragma once
#include "MoveableEntity.h"
class Player : public MoveableEntity
{
public:
	Player();
	~Player();

	//bool Load(const std::string& spriteTexture, sf::Vector2u frameSize, unsigned int numFramesWidth, unsigned int numFramesHeight);

	void Init(ResourceManager* r, GameLevel* g);

	void Action(sf::Vector2f levelpos);
	//void Movement(float dt);
	//void Update(float dt);
	//void Animate(float dt);

	//friend class GameLevel;
	void setTerrainType(int typ);
	void nextTerrainType(int inc);

private:

	void Build(sf::Vector2f fpos);
	void Terraform(sf::Vector2f fpos);

	bool InRange(const sf::Vector2f& levelPos);

	//Data
	GameLevel* pGameLevel;
	float range;

	int terrainType;
};


#pragma once
#include "MoveableEntity.h"
#include "AnimatedSprite.h"

class DebugFella : public MoveableEntity, public AnimatedSprite
{
public:
	DebugFella();
	~DebugFella();

	//bool Load(const std::string& spriteTexture, sf::Vector2u frameSize, unsigned int numFramesWidth, unsigned int numFramesHeight);

	void Init(ResourceManager* r, GameLevel* g);

	void Action(sf::Vector2f levelpos);
	void Movement(float dt) override;	//customise behaviour of these functions
	void Update(float dt) override;
	void Animate(float dt) override;

	//friend class GameLevel;
	void setTerrainType(int typ);
	void nextTerrainType(int inc);

	bool sprinting;
private:
	//sprite sheet animation order
	enum CurrentAnimation {IDLE_SOUTH, IDLE_EAST, IDLE_NORTH, IDLE_WEST, WALKING_SOUTH};

	void Build(sf::Vector2f fpos);
	void Terraform(sf::Vector2f fpos);

	bool InRange(const sf::Vector2f& levelPos);

	//Data
	float range;
	float sprintSpeed;
	int direction;
	int terrainType;
	GameLevel* pGameLevel;
};


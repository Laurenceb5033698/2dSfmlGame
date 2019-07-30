#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

//GameLevel class included here as Entitys will search level for tiles, and intereact with level in general
#include "GameLevel.h"

class ResourceManager;

class MoveableEntity : public Entity, public sf::Sprite
{
public:
	MoveableEntity();
	~MoveableEntity();

	sf::Vector2f& GetVelocity() { return velocity; };

	//Load asset and initialise required rendering data
	//Returns TRUE if Loading FAILS
	bool Load(const std::string& spriteTexture, sf::Vector2u frameSize, unsigned int numFramesWidth, unsigned int numFramesHeight) override;
	
	void Init(ResourceManager* rm) override;
	void Update(float dt) override;
	void Animate(float dt) override;

	void Movement(float dt);

	bool sprinting;

private:
	//friend class GameLevel;
	//sf::Texture m_texture;
	//sf::Vector2u m_frameSize;	//number of pixels per frame
	//sf::Vector2u m_framesDimensions;	//number of frames of animation x and y
	//sf::IntRect* m_frames;

	int direction;
	float speed, sprintSpeed;
	sf::Vector2f velocity;

};


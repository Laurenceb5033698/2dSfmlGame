#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class MoveableEntity : public Entity, public sf::Sprite
{
public:
	MoveableEntity();
	~MoveableEntity();

	sf::Vector2f& GetVelocity() { return velocity; };

	//Load asset and initialise required rendering data
	//Returns TRUE if Loading FAILS
	bool Load(const std::string& spriteTexture, sf::Vector2u frameSize, unsigned int numFramesWidth, unsigned int numFramesHeight);
	void Init();
	void Movement(float dt);
	void Update(float dt);
	void Animate(float dt);

	bool sprinting;

private:
	//sf::Texture m_texture;
	//sf::Vector2u m_frameSize;	//number of pixels per frame
	//sf::Vector2u m_framesDimensions;	//number of frames of animation x and y
	//sf::IntRect* m_frames;

	int direction;
	float speed, sprintSpeed;
	sf::Vector2f velocity;

};


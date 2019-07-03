#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

//A static Entity is a single sprite entity that can be interacted with,
//	however it is not part of any group, and should not be used in bulk.
class StaticEntity :public Entity, public sf::Sprite 
{
public:
	StaticEntity();
	~StaticEntity();

	bool Load(const std::string& spriteTexture, sf::Vector2u frameSize, unsigned int numFramesWidth, unsigned int numFramesHeight);
	void Init();

	void Update(float dt);
	void Animate(float dt);	//Animate is like update but just for animating

private:
	//sf::Texture m_texture;
	////for animation
	//sf::Vector2u m_frameSize;	//number of pixels per frame
	//sf::Vector2u m_framesDimensions;	//number of frames of animation x and y
	//sf::IntRect* m_frames;
};


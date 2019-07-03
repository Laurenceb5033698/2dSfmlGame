#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

//An abstract animatable entity
class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual bool Load(const std::string& spriteTexture, sf::Vector2u frameSize, unsigned int numFramesWidth, unsigned int numFramesHeight) = 0;
	virtual void Init() =0;

	virtual void Update(float dt) =0;
	virtual void Animate(float dt) =0;	//Animate is like update but just for animating

	sf::Texture m_texture;

	//For animation:
	sf::Vector2u m_frameSize;	//number of pixels per frame
	sf::Vector2u m_framesDimensions;	//number of frames of animation x and y
	sf::IntRect* m_frames;
};


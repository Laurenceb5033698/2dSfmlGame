#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Utils.h"

//An abstract animatable entity
//for use alongside sf::sprite
//An Entity adds data to a sprite entity and contains data and functions that would be useful for similar sprite classes
class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual bool Load(const std::string& spriteTexture, sf::Vector2u frameSize, unsigned int numFramesWidth, unsigned int numFramesHeight) = 0;
	
	virtual void Init(ResourceManager* rm) =0;

	virtual void Update(float dt) =0;
	virtual void Animate(float dt) =0;	//Animate is like update but just for animating

	bool LoadTexture(const std::string& textureFilepath);

	ResourceManager * rm;

	sf::Texture m_texture;
	std::shared_ptr<sf::Texture> m_ptexture;
	//For animation:
	sf::Vector2u m_frameSize;	//number of pixels per frame
	sf::Vector2u m_framesDimensions;	//number of frames of animation x and y
	sf::IntRect* m_frames;
};


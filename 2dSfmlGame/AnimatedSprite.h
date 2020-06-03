#pragma once
#include "Sprite.h"



// AnimatedSprite is for single render sprite with multiple frames for animating
//	AnimatedSprite has an animate function that updates the frame for each interval
//	
class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();

	void Init(ResourceManager* rm) override;
	virtual void Animate(float dt);
	//Load asset and initialise required rendering data
	//Returns TRUE if Loading FAILS
	bool Load(const std::string& AnimatedSpriteData) override;

	void setColor(const sf::Color& color);
	void setTextureRect(const sf::IntRect& rectangle);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void SetCurrentAnimation(int index, bool resetframe);
protected:
	void updatePositions();
	void updateTexCoords();

private:
	//Hide Sprite's default Load(), as AnimatedSprite has more advanced loading

	bool LoadAnimData(const std::string& spriteAnimData, std::string& texturefilepath);
	
	float m_animationTimer;
	int m_currentFrame;
	int m_currentAnimation;

public:
	sf::Vertex		m_vertices[4];

	std::vector<sf::Vector2u> m_frameData;

	//For animation:
	sf::Vector2u m_frameSize;	//number of pixels per frame
	
	float m_animationSpeed;

};

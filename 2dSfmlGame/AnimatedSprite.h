#pragma once
#include "Sprite.h"



// AnimatedSprite is for single render sprite with multiple frames for animating
//	AnimatedSprite has an animate function that updates the frame for each interval
//	
class AnimatedSprite : public SingleSprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();

	virtual void Animate(float dt);

	bool Load(const std::string& AnimatedSpriteData) override;

	void SetCurrentAnimation(int index, bool resetframe);

private:
	bool LoadAnimData(const std::string& spriteAnimData, std::string& texturefilepath);
	
	//For animation:
	float m_animationTimer;
	int m_currentFrame;
	int m_currentAnimation;

public:
	std::vector<sf::Vector2u> m_frameData;

	//For animation:
	sf::Vector2u m_frameSize;	//number of pixels per frame
	
	float m_animationSpeed;

};

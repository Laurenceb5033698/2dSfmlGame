#include "AnimatedSprite.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

AnimatedSprite::AnimatedSprite()
	:m_animationSpeed(4), m_animationTimer(0), m_currentAnimation(0)
{
}

AnimatedSprite::~AnimatedSprite()
{

}


//Load asset and initialise required rendering data
//Returns TRUE if Loading FAILS
bool AnimatedSprite::Load(const std::string& AnimatedSpriteData)
{
	std::string textureFilepath;
	if(LoadAnimData(AnimatedSpriteData, textureFilepath))
		return EXIT_FAILURE;


	if (LoadTexture(textureFilepath))
		return EXIT_FAILURE;

	m_currentAnimation = 0;
	
	setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));
	
	return EXIT_SUCCESS;
}


//takes reference to AnimData filepath and a place to store texture filepath
//Reads AnimData, returns texturefilepath by reference
bool AnimatedSprite::LoadAnimData(const std::string& spriteAnimData, std::string& texturefilepath)
{
	//open anim Data
	//read contents
	//saves filepath of spritesheet
	//stores frame size
	//stores vector of pod animation data 
	int framepos(0), frameLength(0);

	std::string line;
	std::stringstream ss;
	std::ifstream file(spriteAnimData);
	if (!file.is_open()) {
		DBOUT("Could not open Anim Data file! :" << spriteAnimData);
		return EXIT_FAILURE;
	}
	else
	{
		//read spritesheet filename
		getline(file, line);
		ss.str(line);
		ss >> texturefilepath;
		ss.clear();
		//read tile pixel dimensions
		getline(file, line);
		ss.str(line);
		ss >> m_frameSize.x >> m_frameSize.y;
		ss.clear();

	
		//get animation frame datas
		while (getline(file, line)) {
			ss.str(line);
			//first is start pos
			//second is number of frames
			ss >> framepos >> frameLength;
			ss.clear();
			m_frameData.push_back(sf::Vector2u(framepos, frameLength));
		}
		

	}

	return EXIT_SUCCESS;
}


void AnimatedSprite::Animate(float deltaTime) 
{

	//animate by advancing frames at constant rate (set to 4 frames per second for now)
	m_animationTimer -= deltaTime;
	if (m_animationTimer < 0)
	{	//Advance Frame

		sf::Vector2u texSize = p_texture->getSize();
		int numframesx = (texSize.x / m_frameSize.x);

		//find frame in sheet
		int modxPos = (m_frameData[m_currentAnimation].x + m_currentFrame) % numframesx;
		int remainPos = (m_frameData[m_currentAnimation].x + m_currentFrame) / numframesx;

		//calculate frame top-left
		sf::Vector2i startPos(modxPos * m_frameSize.x, remainPos *m_frameSize.y);

		//create IntRect from Start Position and Frame Size
		sf::IntRect texRect(startPos, sf::Vector2i(m_frameSize));

		//apply rect
		setTextureRect(texRect);


		if (++m_currentFrame >= m_frameData[m_currentAnimation].y)
			m_currentFrame = 0;
		m_animationTimer = 1 / m_animationSpeed;
	}
}

void AnimatedSprite::SetCurrentAnimation(int index, bool resetframe) 
{
	m_currentAnimation = index;
	if (resetframe) 
	{ 
		m_currentFrame = 0;
		m_animationTimer = -1;
	}
};

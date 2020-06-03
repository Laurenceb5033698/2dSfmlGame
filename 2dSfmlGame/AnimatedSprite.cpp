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

void AnimatedSprite::Init(ResourceManager* rm)
{
	Sprite::Init(rm);
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
	//data and resources now loaded
	//sf::Vector2u texSize = p_texture->getSize();
	//int numframesx = texSize.x / m_frameSize.x;
	//
	////calculate frame pos and size
	//for (int frame(0); frame < m_frameData[0].y; frame++) {
	//	//calc start and end of frame in pixels
	//	int modxPos = (m_frameData[0].x + frame) / numframesx;	//frame number mod 5 for x pos
	//	int remainPos = (m_frameData[0].x + frame) % numframesx;	//frame y number = remainder 5
	//
	//	sf::Vector2i startPos(modxPos * m_frameSize.x, remainPos *m_frameSize.y);
	//
	//	sf::IntRect texRect(startPos, sf::Vector2i(m_frameSize));
	//} //animation handed in Animate()


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
	//stores vector of animation data 
	//std::string spriteSheetFilepath;
	//int frameWidth(0), frameHeight(0);
	int framepos(0), frameLength(0);

	std::string line, str;
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

	//animate by advancing frames at constant rate (4 frames per second)
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










void AnimatedSprite::setTextureRect(const sf::IntRect& rectangle)
{
	if (rectangle != m_textureRect)
	{
		m_textureRect = rectangle;
		updatePositions();
		updateTexCoords();
	}
}
void AnimatedSprite::updatePositions() {
	sf::FloatRect bounds = getLocalBounds();

	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(0, bounds.height);
	m_vertices[2].position = sf::Vector2f(bounds.width, 0);
	m_vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
}

void AnimatedSprite::updateTexCoords() {
	float left = static_cast<float>(m_textureRect.left);
	float right = left + m_textureRect.width;
	float top = static_cast<float>(m_textureRect.top);
	float bottom = top + m_textureRect.height;

	m_vertices[0].texCoords = sf::Vector2f(left, top);
	m_vertices[1].texCoords = sf::Vector2f(left, bottom);
	m_vertices[2].texCoords = sf::Vector2f(right, top);
	m_vertices[3].texCoords = sf::Vector2f(right, bottom);
}

void AnimatedSprite::setColor(const sf::Color& color) {
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;

}
void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &(*p_texture);//Dereference shared_ptr, then pass texture to renderStates

	// draw the vertex array
	target.draw(m_vertices, 4, sf::PrimitiveType::TriangleStrip, states);

}
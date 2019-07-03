#include "StaticEntity.h"

StaticEntity::StaticEntity()
{
}


StaticEntity::~StaticEntity()
{
}

void StaticEntity::Init() 
{
}


//Load asset and initialise required rendering data
//Returns TRUE if Loading FAILS
bool StaticEntity::Load(const std::string& spriteTexture, sf::Vector2u frameSizePx, unsigned int numFramesWidth, unsigned int numFramesHeight)
{

	if (!Entity::m_texture.loadFromFile(spriteTexture)) {
		DBOUT( "failed to load texture" << spriteTexture)
		return EXIT_FAILURE;

	}
	setTexture(Entity::m_texture);

	//frames, as in animation frames
	m_frameSize = frameSizePx;
	m_framesDimensions = sf::Vector2u(numFramesWidth, numFramesHeight);

	//create intRects for each frame of animation in the sprite
	m_frames = new sf::IntRect[numFramesWidth*numFramesHeight];
	for (int j(0); j < numFramesHeight; ++j)
		for (int i(0); i < numFramesWidth; ++i)
			m_frames[i + j * numFramesHeight] = sf::IntRect(i*frameSizePx.x, j*frameSizePx.y, frameSizePx.x, frameSizePx.y);


	setTextureRect(m_frames[0]);
	return EXIT_SUCCESS;
}


void StaticEntity::Update(float dt) 
{
}


void StaticEntity::Animate(float dt)
{
}

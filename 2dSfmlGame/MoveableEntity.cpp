#include "MoveableEntity.h"
#include "sfVectorMath.h"

MoveableEntity::MoveableEntity() :
	direction(0),
	speed(100),
	sprintSpeed(240),
	sprinting(false)
{

}


MoveableEntity::~MoveableEntity()
{

}

void MoveableEntity::Init(ResourceManager* r)
{
	rm = r;
	setPosition(0, 0);
	setOrigin(32, 32);
}


//Load asset and initialise required rendering data
//Returns TRUE if Loading FAILS
bool MoveableEntity::Load(const std::string& spriteTexture, sf::Vector2u frameSizePx, unsigned int numFramesWidth, unsigned int numFramesHeight) 
{
	if (LoadTexture(spriteTexture))	
		return EXIT_FAILURE;

	setTexture(*m_ptexture);

	//frames, as in animation frames
	m_frameSize = frameSizePx;
	m_framesDimensions = sf::Vector2u(numFramesWidth, numFramesHeight);

	//create intRects for each frame of animation in the sprite
	m_frames = new sf::IntRect[numFramesWidth*numFramesHeight];
	for (int j(0); j < numFramesHeight; ++j) 
		for (int i(0); i < numFramesWidth; ++i)
			m_frames[i + j * numFramesHeight] = sf::IntRect(i*frameSizePx.x, j*frameSizePx.y, frameSizePx.x, frameSizePx.y);


	setTextureRect(m_frames[direction]);
	return EXIT_SUCCESS;
}


void MoveableEntity::Update(float deltaTime) {
	Movement(deltaTime);

	velocity = sf::Vector2f(0, 0);
}
void MoveableEntity::Animate(float deltaTime) {
	if (velocity.x != 0 || velocity.y != 0) {

		//down =0, right=1, up = 2, left = 3
		if (velocity.y == 0)
			direction = velocity.x > 0 ? 1 : 3;
		if (velocity.x == 0)
			direction = velocity.y > 0 ? 0 : 2;

		setTextureRect(m_frames[direction]);
	}
}


void MoveableEntity::Movement(float dt) {
	
	float mag( sfm::length(velocity) );
	if (mag > 0) {
		velocity /= mag;//normalize
		move(velocity * dt * (sprinting ? sprintSpeed : speed) );
	}
}

//void Builder::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	// apply the transform
//	states.transform *= getTransform();
//
//	
//	// apply the tileset texture
//	states.texture = &m_texture;
//
//	// draw the vertex array
//	target.draw(m_vertices, states);
//}
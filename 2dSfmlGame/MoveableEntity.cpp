#include "MoveableEntity.h"
#include "sfVectorMath.h"

MoveableEntity::MoveableEntity() :
	speed(100), m_velocity(0,0)
{

}


MoveableEntity::~MoveableEntity()
{

}


void MoveableEntity::Update(float deltaTime) {
	Movement(deltaTime);

	m_velocity = sf::Vector2f(0, 0);
}



//void MoveableEntity::Movement(float dt) {
//	
//	float mag( sfm::length(m_velocity) );
//	if (mag > 0) {
//		m_velocity /= mag;//normalize
//		m_position +=(m_velocity * dt * speed);
//	}
//}

#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

//GameLevel class included here as Entitys will search level for tiles, and intereact with level in general
#include "GameLevel.h"

//ABSTRACT
class MoveableEntity : public Entity
{
public:
	MoveableEntity();
	~MoveableEntity();
	sf::Vector2f& GetVelocity() { return m_velocity; };
	float& GetSpeed() { return speed; };

	void Update(float dt) ;

	virtual void Movement(float dt) =0;



private:
	
	float speed;
	sf::Vector2f m_velocity;

};


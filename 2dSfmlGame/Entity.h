#pragma once
#include "Utils.h"

//An abstract entity
//for use alongside sf::sprite or any other drawable class
//An Entity adds data to a sprite entity and contains data and functions that would be useful for similar sprite classes
//ultimately provides a very basic class that can be used in polymorphic places
class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float dt) =0;
	
};


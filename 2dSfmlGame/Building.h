#pragma once
#include "Sprite.h"	//for singlesprite
#include "Team.h"

//a Building is an entity that doesnt move, but can be updated and can be place/removed during runtime
//A Building:
//	-costs resources to place
//	-must be place on a free tile
//	-belongs to a team
//	-consists of one sprite
//	-can be clicked on
//	-can be intereacted with
//	-does something/has purpose
//	-should have collision boxs
class Building : public SingleSprite
{
public:
	Building(Team* myTeam);
	virtual ~Building();

	void Init(ResourceManager* rm) override;


	//references
	Team* p_myTeam;
	//data
};


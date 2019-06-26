#pragma once
#include <SFML/Graphics.hpp>
class SingleSprite : public sf::Drawable, public sf::Transformable
{
public:
	SingleSprite();
	~SingleSprite();

	bool load();
};


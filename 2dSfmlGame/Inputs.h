#pragma once

#include <SFML/Graphics.hpp>

class Inputs
{
public:
	Inputs();
	~Inputs();

	struct KeyVal //keyboard states
	{	
		bool onPressed;	//onpressed states last for 1 update
		bool onReleased;
		bool isPressed;	//ispressed lasts untill released
	};

	void Press(sf::Keyboard::Key);
	void Release(sf::Keyboard::Key);
	void Update();
	void Reset();

	bool onPressed(sf::Keyboard::Key k);
	bool onReleased(sf::Keyboard::Key k);
	bool isPressed(sf::Keyboard::Key k);
	//array of keyboard states
	KeyVal* keys;
};


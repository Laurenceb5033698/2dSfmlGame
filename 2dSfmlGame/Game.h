#pragma once
#include <SFML/Graphics.hpp>

//Game class holds all game systems and handles update and render call.
class Game
{
public:
	Game(sf::Uint32 windowWidth, sf::Uint32 windowHeight, std::string title);
	~Game();

	void update(sf::Time elapsed);
	void render();

	sf::Window* mWindow;
};


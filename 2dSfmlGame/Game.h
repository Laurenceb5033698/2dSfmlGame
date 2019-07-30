#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Inputs.h"
//#include "TileMap.h"
#include "MoveableEntity.h"
#include "Player.h"
#include "ResourceManager.h"
#include "GameLevel.h"
//Game class holds all game systems and handles update and render call.
class Game
{
public:
	Game();
	~Game();

	void run();
	void update(float elapsed);
	void render();
	void handleInputs();
	void HandleEvents();

	bool load();
	void init();
	void SetupGame();
	void InitWindow();

	bool paused;

	sf::RenderWindow mWindow;
	sf::View view;
	Inputs inputs;
	ResourceManager resourceManager;

	//TileMap map;
	Player guy;
	GameLevel gameLevel;

};




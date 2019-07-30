#include "Game.h"
#include <random>

Game::Game():
	paused(false)
{
}


Game::~Game()
{

}

bool Game::load() {
	

	//tilemap. todo move to make tilemap load from a level-data class
	//tilemap class should be a tool that game class uses to load levels
	
	if (gameLevel.LoadTilemap("resources/levelData/level2.txt"))
	{
		DBOUT("reading loading tilemap failed.");
		return EXIT_FAILURE;
	}


	if (guy.Load("resources/sprites/man_sprite.png",sf::Vector2u(64,64),4,1))
		return EXIT_FAILURE;
	


	return EXIT_SUCCESS;


}

//Initialise objects before loading
void Game::init() {
	InitWindow();
	
	srand(0);
	gameLevel.Init(&resourceManager);
	guy.Init(&resourceManager, &gameLevel);
}

//Setup Game objects after loading
void Game::SetupGame()
{
	guy.setPosition(gameLevel.getCentre());

}

///Update should onyl contin logic that will be ok with being paused
void Game::update(float elapsed) {
	handleInputs();	//user inputs for this game tick
	//game logic
	guy.Update(elapsed);

}

void Game::render() {
	if (!mWindow.isOpen())
		return;

	//set viewport
	view.setCenter(guy.getPosition());
	mWindow.setView(view);

	//draw
	mWindow.clear();
	gameLevel.Draw(mWindow);
	mWindow.draw(guy);
	mWindow.display();
}


void Game::handleInputs() {
	

	if (inputs.isPressed(sf::Keyboard::D)) 
	{
		guy.GetVelocity() += sf::Vector2f(1.0f, 0);
	}
	if (inputs.isPressed(sf::Keyboard::A))
	{
		guy.GetVelocity() += sf::Vector2f(-1.0f, 0);

	}
	if (inputs.isPressed(sf::Keyboard::S))
	{
		guy.GetVelocity() += sf::Vector2f(0, 1.0f);

	}
	if (inputs.isPressed(sf::Keyboard::W))
	{
		guy.GetVelocity() += sf::Vector2f(0, -1.0f);

	}

	//change terraintype
	if (inputs.onPressed(sf::Keyboard::Q))
		guy.nextTerrainType(-1);
	if (inputs.onPressed(sf::Keyboard::E))
		guy.nextTerrainType(+1);
	
	guy.sprinting = (inputs.isPressed(sf::Keyboard::LShift));
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f fpos( mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));
		//determine if user clicked on UI or interactable

		//else try to do player action
		guy.Action(fpos);


	}


}

void Game::HandleEvents() {
	inputs.Update();	//reset any onpressed/onreleased states

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{	//close window, therefore quit game
			mWindow.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			inputs.Press(event.key.code);
		}
		if (event.type == sf::Event::KeyReleased) {
			inputs.Release(event.key.code);
		}
		
	}//end Event processing

	//although its a user input and not an sf::Event, the pause command should be outside of the pause conditional
	if (inputs.onPressed(sf::Keyboard::P))
		paused = !paused;
}


void Game::InitWindow() {

	//TODO
	//find out screen dimensions
	//fullscreen or naw
	//load settings from previous game

	//creates game window. todo creat window from loaded settings
	mWindow.create(sf::VideoMode(1280, 720), "Tile Game");
	mWindow.setVerticalSyncEnabled(false);
	mWindow.setFramerateLimit(60);
	mWindow.setKeyRepeatEnabled(false);
	
	//init View
	view.setSize(1280, 720);
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(0.8f);
}

void Game::run() {


	if (!load()) {
		//game loaded successfully, run game
		SetupGame();

		sf::Clock clock;
		sf::Time start, end;
		float elapsed(0.0f);
		while (mWindow.isOpen())//game ends when window is closed
		{	
			//start watching clock
			start = clock.getElapsedTime();
			//Event handling is separated from game update to avoid pausing system inputs
			HandleEvents();

			if(!paused)
				update(elapsed);//uses time elapsed of last call

			render();
			

			//find time elapsed
			end = clock.getElapsedTime();

			elapsed = end.asSeconds() - start.asSeconds();
		}
	}
	else {
		DBOUT("Error Loading Game! Quitting...");
	}
}
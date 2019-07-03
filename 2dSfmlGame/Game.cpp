#include "Game.h"



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
	const int level[] =
	{
		0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 0, 1, 0, 3, 3, 7, 7, 3, 3, 3, 3,
		0, 1, 0, 1, 2, 0, 3, 3, 3, 7, 11, 11, 11, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 3, 11, 15, 15, 4, 5, 5,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 3, 7, 11, 11, 8, 9, 9,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 3, 7, 7, 12, 13, 13,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	if (map.load("resources/Tilecrap.png", sf::Vector2u(64, 64), level, 16, 8))
		return EXIT_FAILURE;
	
	if (guy.Load("resources/man_sprite.png",sf::Vector2u(64,64),4,1))
		return EXIT_FAILURE;
	
	return EXIT_SUCCESS;


}

void Game::init() {
	InitWindow();


	guy.Init();
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
	mWindow.draw(map);
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
	
	guy.sprinting = (inputs.isPressed(sf::Keyboard::LShift));
		

	if(inputs.onPressed(sf::Keyboard::C))
	{
		map.changeTile(guy.getPosition(), 3);
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
	view.zoom(0.5f);
}

void Game::run() {

	if (!load()) {
		//game loaded successfully, run game

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
}
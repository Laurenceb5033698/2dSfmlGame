#include "Game.h"



Game::Game(sf::Uint32 windowWidth, sf::Uint32 windowHeight, std::string title)
{
	mWindow = new sf::Window(sf::VideoMode(windowWidth, windowHeight), title);
}


Game::~Game()
{
	delete mWindow;
}

void Game::update(sf::Time elapsed) {

}

void Game::render() {

}
#include <SFML/Graphics.hpp>
#include "TileMap.h"

int WinMain()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::CircleShape man(20.f);
	man.setPosition(10, 10);

	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 7, 7, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 7, 11, 11, 11, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 3, 11, 15, 15, 4, 5, 5,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 3, 7, 11, 11, 8, 9, 9,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 3, 7, 7, 12, 13, 13,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	TileMap map;
	if (!map.load("resources/Tilecrap.png", sf::Vector2u(64, 64), level, 16, 8))
		return -1;

	sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(0.5f);
	sf::Clock GameClock;
	while (window.isOpen())
	{
		sf::Time elapsed = GameClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			sf::Vector2f manmovement(0.f,0.f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				manmovement += sf::Vector2f(-0.5f, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				manmovement += sf::Vector2f(0.5f, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				manmovement += sf::Vector2f(0,-0.5f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				manmovement += sf::Vector2f(0, 0.5f);
			}

			man.move(manmovement);
		}

		view.setCenter(man.getPosition());

		window.setView(view);

		window.clear();
		window.draw(map);
		window.draw(man);
		window.display();
	}

	return 0;
}


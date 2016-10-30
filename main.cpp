#include <SFML/Graphics.hpp>
#include "Agent.h"

int main()
{
	sf::VideoMode vm(1280, 720);
	sf::RenderWindow window(vm, "Platoon!");

	sf::View gameView(sf::FloatRect(0, 0, 1920, 1080));

	Agent agent("Assets/characters.png");

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		window.setView(gameView);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// update
		agent.Update(dt.asSeconds());

		//draw
		agent.Draw(window);

		window.display();
	}

	return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Agent.h"
#include "World.h"

int main()
{
	sf::VideoMode vm(1280, 720);
	sf::RenderWindow window(vm, "Platoon!");

	sf::View gameView(sf::FloatRect(0, 0, 1280, 720));

	//obstacles
	std::vector<Obstacle> obstacles;
	//obstacles.push_back(Obstacle(200, 50, 100, 100));
	
	// agents
	Agent ag("Assets/character1.png");
	std::vector<Agent> agents;
	agents.push_back(ag);
	
	World world(obstacles, agents);

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

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				
				std::vector<Agent>& worldAgents = world.GetAgents();
				for (std::vector<Agent>::iterator it = worldAgents.begin(); it != worldAgents.end(); ++it)
				{
					it->SetTarget(glm::vec2(mouse.x, mouse.y));
				}
			}
		}

		window.clear();
		
		// update
		world.Update(dt.asSeconds());

		//draw
		world.Draw(window);

		window.display();
	}

	return 0;
}

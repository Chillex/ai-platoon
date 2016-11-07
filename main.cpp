#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <iostream>

#include "Agent.h"
#include "World.h"
#include "SteeringManager.h"
#include "Arrive.h"
#include "LookWhereYouAreGoing.h"
#include "Persue.h"
#include "Evade.h"

char* GetRandomCharacterImagePath()
{
	int r = rand() % 3;

	switch (r)
	{
	case 1:
		return "Assets/character1.png";
	case 2:
		return "Assets/character2.png";
	default:
		return "Assets/character3.png";
	}
}

int main()
{
	sf::VideoMode vm(1280, 720);
	sf::RenderWindow window(vm, "Platoon!");

	sf::View gameView(sf::FloatRect(0, 0, 1280, 720));

	//obstacles
	std::vector<Obstacle*> obstacles;
	//obstacles.push_back(new Obstacle(200, 50, 100, 100));
	
	// agents
	std::vector<Agent*> agents;
	Agent* arriveAgent = new Agent("Assets/character1.png", glm::vec2(100.0f));
	Agent* persueAgent = new Agent("Assets/character2.png", glm::vec2(500.0f));

	arriveAgent->steeringManager->AddBehavior(new Arrive(), 1.0f);
	arriveAgent->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	persueAgent->steeringManager->AddBehavior(new Persue(arriveAgent, 5.0f), 1.0f);
	persueAgent->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	agents.push_back(arriveAgent);
	agents.push_back(persueAgent);
	
	World world(obstacles, agents);

	sf::Texture targetTexture;
	targetTexture.loadFromFile("Assets/target.png");
	sf::Sprite targetSprite(targetTexture, sf::IntRect(0, 0, 24, 24));
	targetSprite.setOrigin(12, 12);
	targetSprite.setPosition(-50, -50);

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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				if(event.mouseButton.button == sf::Mouse::Left)
				{
					targetSprite.setPosition(mouse);

					std::vector<Agent*>& worldAgents = world.GetAgents();
					for (std::vector<Agent*>::iterator it = worldAgents.begin(); it != worldAgents.end(); ++it)
					{
						(*it)->target.position = glm::vec2(mouse.x, mouse.y);
					}
				}
				
				//if(event.mouseButton.button == sf::Mouse::Right)
				//{
				//	Agent* newAgent = new Agent(GetRandomCharacterImagePath(), glm::vec2(mouse.x, mouse.y));
				//	newAgent->target.position = glm::vec2(targetSprite.getPosition().x, targetSprite.getPosition().y);
				//	world.AddAgent(newAgent);
				//}
			}
		}

		window.clear(sf::Color::White);
		
		// update
		world.Update(dt.asSeconds());

		//draw
		window.draw(targetSprite);
		world.Draw(window);

		window.display();
	}

	return 0;
}

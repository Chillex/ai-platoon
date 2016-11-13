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
#include "Seperation.h"
#include "Path.h"
#include "PathFollowing.h"
#include "Obstacle.h"
#include "CollisionAvoidance.h"

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

	Path platoonPath;
	//path.GenerateRandomPath(10);
	platoonPath.AddWaypoint(100.0f, 50.0f);
	platoonPath.AddWaypoint(200.0f, 100.0f);
	platoonPath.AddWaypoint(400.0f, 100.0f);
	platoonPath.AddWaypoint(500.0f, 150.0f);
	platoonPath.AddWaypoint(450.0f, 300.0f);
	platoonPath.AddWaypoint(150.0f, 350.0f);
	platoonPath.AddWaypoint(100.0f, 550.0f);
	platoonPath.AddWaypoint(200.0f, 650.0f);
	platoonPath.AddWaypoint(500.0f, 650.0f);
	platoonPath.AddWaypoint(700.0f, 550.0f);
	platoonPath.AddWaypoint(800.0f, 350.0f);
	platoonPath.AddWaypoint(850.0f, 150.0f);
	platoonPath.AddWaypoint(1150.0f, 100.0f);
	platoonPath.AddWaypoint(1050.0f, 400.0f);
	platoonPath.AddWaypoint(1150.0f, 600.0f);

	Path enemyPath;
	enemyPath.AddWaypoint(750.0f, 250.0f);
	enemyPath.AddWaypoint(950.0f, 275.0f);
	enemyPath.AddWaypoint(1150.0f, 300.0f);

	//obstacles
	std::vector<Obstacle*> obstacles;
	obstacles.push_back(new Obstacle(150, 150, 250, 130));
	obstacles.push_back(new Obstacle(200, 200, 250, 370));
	obstacles.push_back(new Obstacle(50, 150, 950, 50));
	
	// agents
	std::vector<Agent*> agents;
	Agent* platoon1 = new Agent("Assets/character1.png", glm::vec2(80.0f, 70.0f), 20.0f, sf::Color::Red, 25, 1);
	Agent* platoon2 = new Agent("Assets/character2.png", glm::vec2(120.0f, 30.0f), 20.0f, sf::Color::Green, 25, 1);
	Agent* platoon3 = new Agent("Assets/character3.png", glm::vec2(80.0f, 30.0f), 20.0f, sf::Color::Blue, 25, 1);
	Agent* platoon4 = new Agent("Assets/character2.png", glm::vec2(120.0f, 70.0f), 20.0f, sf::Color::Yellow, 25, 1);

	//agent1->steeringManager->AddBehavior(new Arrive(), 1.0f);
	platoon1->steeringManager->AddBehavior(new PathFollowing(platoonPath, true), 1.0f);
	platoon1->steeringManager->AddBehavior(new Seperation(), 5.0f);
	//platoon1->steeringManager->AddBehavior(new CollisionAvoidance(1.0f), 2.0f);
	platoon1->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	//agent2->steeringManager->AddBehavior(new Arrive(), 1.0f);
	platoon2->steeringManager->AddBehavior(new PathFollowing(platoonPath, true), 1.0f);
	//agent2->steeringManager->AddBehavior(new Persue(arriveAgent, 5.0f), 1.0f);
	platoon2->steeringManager->AddBehavior(new Seperation(), 5.0f);
	platoon2->steeringManager->AddBehavior(new CollisionAvoidance(1.0f), 2.0f);
	platoon2->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	platoon3->steeringManager->AddBehavior(new PathFollowing(platoonPath, true), 1.0f);
	platoon3->steeringManager->AddBehavior(new Seperation(), 5.0f);
	platoon3->steeringManager->AddBehavior(new CollisionAvoidance(1.0f), 2.0f);
	platoon3->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	platoon4->steeringManager->AddBehavior(new PathFollowing(platoonPath, true), 1.0f);
	platoon4->steeringManager->AddBehavior(new Seperation(), 5.0f);
	platoon4->steeringManager->AddBehavior(new CollisionAvoidance(1.0f), 2.0f);
	platoon4->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	agents.push_back(platoon1);
	agents.push_back(platoon2);
	agents.push_back(platoon3);
	agents.push_back(platoon4);

	Agent* enemy1 = new Agent("Assets/enemy1.png", glm::vec2(750.0f, 250.0f), 20.0f, sf::Color::White, 0, 2);
	Agent* enemy2 = new Agent("Assets/enemy2.png", glm::vec2(1150.0f, 300.0f), 20.0f, sf::Color::White, 0, 2);

	enemy1->steeringManager->AddBehavior(new PathFollowing(enemyPath, true), 1.0f);
	enemy1->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	enemy2->steeringManager->AddBehavior(new PathFollowing(enemyPath, true), 1.0f);
	enemy2->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);

	agents.push_back(enemy1);
	agents.push_back(enemy2);
	
	World world(obstacles, agents, true);

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

				//if(event.mouseButton.button == sf::Mouse::Left)
				//{
				//	targetSprite.setPosition(mouse);

				//	const std::vector<Agent*>& worldAgents = world.GetAgents();
				//	for (std::vector<Agent*>::const_iterator it = worldAgents.begin(); it != worldAgents.end(); ++it)
				//	{
				//		(*it)->target.position = glm::vec2(mouse.x, mouse.y);
				//	}
				//}
				
				//if(event.mouseButton.button == sf::Mouse::Right)
				//{
				//	Agent* newAgent = new Agent(GetRandomCharacterImagePath(), glm::vec2(mouse.x, mouse.y), sf::Color::White, 0);
				//	newAgent->steeringManager->AddBehavior(new Arrive(), 1.0f);
				//	newAgent->steeringManager->AddBehavior(new Seperation(50.0f), 5.0f);
				//	newAgent->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f);
				//	newAgent->target.position = glm::vec2(targetSprite.getPosition().x, targetSprite.getPosition().y);
				//	world.AddAgent(newAgent);
				//}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::R)
				{
					platoonPath.GenerateRandomPath(10);
				}

				if (event.key.code == sf::Keyboard::D)
				{
					world.ToggleDebug();
				}
			}
		}

		window.clear(sf::Color::White);
		
		// update
		world.Update(dt.asSeconds());

		//draw
		window.draw(targetSprite);
		world.Draw(window);

		if(world.IsDebuggingMode())
		{
			platoonPath.Draw(window);
		}

		window.display();
	}

	return 0;
}

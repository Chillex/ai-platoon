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
#include "ObstacleAvoidance.h"
#include "Formation.h"

int main()
{
	sf::VideoMode vm(1280, 720);
	sf::RenderWindow window(vm, "Platoon!");

	sf::View gameView(sf::FloatRect(0, 0, 1280, 720));

	Path platoonPath;
	platoonPath.color = sf::Color(107, 142, 35);
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
	platoonPath.AddWaypoint(1250.0f, 400.0f);
	platoonPath.AddWaypoint(1150.0f, 600.0f);

	Path enemyPath1;
	enemyPath1.AddWaypoint(10.0f, 382.0f);
	enemyPath1.AddWaypoint(159.0f, 420.0f);
	enemyPath1.AddWaypoint(343.0f, 469.0f);
	enemyPath1.AddWaypoint(353.0f, 602.0f);
	enemyPath1.AddWaypoint(363.0f, 717.0f);

	Path enemyPath2;
	enemyPath2.AddWaypoint(970.0f, 10.0f);
	enemyPath2.AddWaypoint(1020.0f, 80.0f);
	enemyPath2.AddWaypoint(1080.0f, 165.0f);
	enemyPath2.AddWaypoint(1180.0f, 170.0f);
	enemyPath2.AddWaypoint(1270.0f, 180.0f);

	// obstacles
	std::vector<Obstacle*> obstacles;
	// obstacle group top left
	obstacles.push_back(new Obstacle(sf::FloatRect(342, 142, 45, 45), 65.0f, "Assets/obstacle_small.png", sf::Vector2f(70.0f, 70.0f)));
	obstacles.push_back(new Obstacle(sf::FloatRect(422, 42, 45, 45), -25.0f, "Assets/obstacle_small.png", sf::Vector2f(70.0f, 70.0f)));
	obstacles.push_back(new Obstacle(sf::FloatRect(572, 122, 45, 45), 25.0f, "Assets/obstacle_small.png", sf::Vector2f(70.0f, 70.0f)));
	obstacles.push_back(new Obstacle(sf::FloatRect(447, 272, 45, 45), 0.0f, "Assets/obstacle_small.png", sf::Vector2f(70.0f, 70.0f)));
	// obstacle group center right
	obstacles.push_back(new Obstacle(sf::FloatRect(710, 315, 90, 200), 25.0f, "Assets/obstacle_long.png", sf::Vector2f(70.0f, 140.0f)));
	obstacles.push_back(new Obstacle(sf::FloatRect(910, 400, 90, 200), 25.0f, "Assets/obstacle_long.png", sf::Vector2f(70.0f, 140.0f)));
	// obstacle right end
	obstacles.push_back(new Obstacle(sf::FloatRect(1170, 500, 75, 75), 45.0f, "Assets/obstacle.png", sf::Vector2f(70.0f, 70.0f)));

	// agents
	float sperationRadius = 20.0f;
	float lookAhead = 100.0f;
	std::vector<Agent*> agents;
	Agent* platoon1 = new Agent("Assets/character1.png", glm::vec2(140.0f, 80.0f), sperationRadius, lookAhead, sf::Color(255, 177, 164), 25, 1);
	Agent* platoon2 = new Agent("Assets/character2.png", glm::vec2(100.0f, 40.0f), sperationRadius, lookAhead, sf::Color(173, 229, 159), 25, 1);
	Agent* platoon3 = new Agent("Assets/character3.png", glm::vec2(100.0f, 120.0f), sperationRadius, lookAhead, sf::Color(191, 156, 242), 25, 1);
	Agent* platoon4 = new Agent("Assets/character2.png", glm::vec2(60.0f, 160.0f), sperationRadius, lookAhead, sf::Color(235, 214, 151), 25, 1);

	PriorityGroup group0;
	group0.priority = 0;
	group0.behaviors.push_back(BlendedBehavior{ new ObstacleAvoidance(), 1.5f });
	group0.behaviors.push_back(BlendedBehavior{ new CollisionAvoidance(1.0f), 1.0f });

	PriorityGroup group1;
	group1.priority = 1;
	group1.behaviors.push_back(BlendedBehavior{ new Seperation(), 1.0f });

	PriorityGroup group2;
	group2.priority = 2;
	group2.behaviors.push_back(BlendedBehavior{ new Arrive(), 1.0f });
	group2.behaviors.push_back(BlendedBehavior{ new Align(), 1.0f });

	platoon1->steeringManager->AddBehaviorGroup(group0);
	platoon1->steeringManager->AddBehaviorGroup(group1);
	platoon1->steeringManager->AddBehaviorGroup(group2);

	platoon2->steeringManager->AddBehaviorGroup(group0);
	platoon2->steeringManager->AddBehaviorGroup(group1);
	platoon2->steeringManager->AddBehaviorGroup(group2);

	platoon3->steeringManager->AddBehaviorGroup(group0);
	platoon3->steeringManager->AddBehaviorGroup(group1);
	platoon3->steeringManager->AddBehaviorGroup(group2);

	platoon4->steeringManager->AddBehaviorGroup(group0);
	platoon4->steeringManager->AddBehaviorGroup(group1);
	platoon4->steeringManager->AddBehaviorGroup(group2);

	agents.push_back(platoon1);
	agents.push_back(platoon2);
	agents.push_back(platoon3);
	agents.push_back(platoon4);

	// platoon formation
	std::vector<Agent*> platoonFormationAgents;
	platoonFormationAgents.push_back(platoon1);
	platoonFormationAgents.push_back(platoon2);
	platoonFormationAgents.push_back(platoon3);
	platoonFormationAgents.push_back(platoon4);

	std::vector<glm::vec2> platoonPositionOffsets;
	platoonPositionOffsets.push_back(glm::vec2(-30.0f, -50.0f));
	platoonPositionOffsets.push_back(glm::vec2(-70.0f, 0.0f));
	platoonPositionOffsets.push_back(glm::vec2(30.0f, 0.0f));
	platoonPositionOffsets.push_back(glm::vec2(70.0f, 50.0f));

	std::vector<float> platoonOrientationOffsets;
	platoonOrientationOffsets.push_back(0.0f);
	platoonOrientationOffsets.push_back(-90.0f);
	platoonOrientationOffsets.push_back(45.0f);
	platoonOrientationOffsets.push_back(180.0f);

	Formation* platoonFormation = new Formation(platoonFormationAgents, platoonPositionOffsets, platoonOrientationOffsets);
	platoonFormation->position = glm::vec2(100.0f, 50.0f);
	platoonFormation->steeringManager->AddBehaviorGroup(PriorityGroup{ {}, 0 });
	platoonFormation->steeringManager->AddBehavior(new PathFollowing(platoonPath, false), 1.0f, 0);
	platoonFormation->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f, 0);
	platoonFormation->SetFormationSpeed(70.0f);

	// enemies
	Agent* enemy1 = new Agent("Assets/enemy1.png", glm::vec2(10.0f, 342.0f), sperationRadius, lookAhead, sf::Color::White, 0, 2);
	Agent* enemy2 = new Agent("Assets/enemy2.png", glm::vec2(-30.0f, 382.0f), sperationRadius, lookAhead, sf::Color::White, 0, 2);
	Agent* enemy3 = new Agent("Assets/enemy1.png", glm::vec2(50.0f, 382.0f), sperationRadius, lookAhead, sf::Color::White, 0, 2);
	Agent* enemy4 = new Agent("Assets/enemy2.png", glm::vec2(1000.0f, 10.0f), sperationRadius, lookAhead, sf::Color::White, 0, 2);
	Agent* enemy5 = new Agent("Assets/enemy1.png", glm::vec2(940.0f, 10.0f), sperationRadius, lookAhead, sf::Color::White, 0, 2);

	PriorityGroup enemyGroup0;
	enemyGroup0.priority = 0;
	enemyGroup0.behaviors.push_back(BlendedBehavior{ new Arrive(), 1.0f });
	enemyGroup0.behaviors.push_back(BlendedBehavior{ new LookWhereYouAreGoing(), 1.0f });

	enemy1->steeringManager->AddBehaviorGroup(enemyGroup0);
	enemy2->steeringManager->AddBehaviorGroup(enemyGroup0);
	enemy3->steeringManager->AddBehaviorGroup(enemyGroup0);
	enemy4->steeringManager->AddBehaviorGroup(enemyGroup0);
	enemy5->steeringManager->AddBehaviorGroup(enemyGroup0);

	agents.push_back(enemy1);
	agents.push_back(enemy2);
	agents.push_back(enemy3);
	agents.push_back(enemy4);
	agents.push_back(enemy5);

	// enemy formation 1
	std::vector<Agent*> enemyFormation1Agents;
	enemyFormation1Agents.push_back(enemy1);
	enemyFormation1Agents.push_back(enemy2);
	enemyFormation1Agents.push_back(enemy3);

	std::vector<glm::vec2> enemyPositionOffsets1;
	enemyPositionOffsets1.push_back(glm::vec2(0.0f, -40.0f));
	enemyPositionOffsets1.push_back(glm::vec2(-40.0f, 0.0f));
	enemyPositionOffsets1.push_back(glm::vec2(40.0f, 0.0f));

	std::vector<float> enemyOrientationOffsets1;
	enemyOrientationOffsets1.push_back(0.0f);
	enemyOrientationOffsets1.push_back(0.0f);
	enemyOrientationOffsets1.push_back(5.0f);

	Formation* enemyFormation1 = new Formation(enemyFormation1Agents, enemyPositionOffsets1, enemyOrientationOffsets1);
	enemyFormation1->position = glm::vec2(10.0f, 382.0f);
	enemyFormation1->steeringManager->AddBehaviorGroup(PriorityGroup{ {}, 0 });
	enemyFormation1->steeringManager->AddBehavior(new PathFollowing(enemyPath1, true), 1.0f, 0);
	enemyFormation1->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f, 0);
	enemyFormation1->SetFormationSpeed(80.0f);

	// enemy formation 2
	std::vector<Agent*> enemyFormation2Agents;
	enemyFormation2Agents.push_back(enemy4);
	enemyFormation2Agents.push_back(enemy5);

	std::vector<glm::vec2> enemyPositionOffsets2;
	enemyPositionOffsets2.push_back(glm::vec2(30.0f, 0.0));
	enemyPositionOffsets2.push_back(glm::vec2(-30.0f, 0.0f));

	std::vector<float> enemyOrientationOffsets2;
	enemyOrientationOffsets2.push_back(0.0f);
	enemyOrientationOffsets2.push_back(0.0f);

	Formation* enemyFormation2 = new Formation(enemyFormation2Agents, enemyPositionOffsets2, enemyOrientationOffsets2);
	enemyFormation2->position = glm::vec2(970.0f, 10.0f);
	enemyFormation2->steeringManager->AddBehaviorGroup(PriorityGroup{ {}, 0 });
	enemyFormation2->steeringManager->AddBehavior(new PathFollowing(enemyPath2, true), 1.0f, 0);
	enemyFormation2->steeringManager->AddBehavior(new LookWhereYouAreGoing(), 1.0f, 0);
	enemyFormation2->SetFormationSpeed(70.0f);

	World world(obstacles, agents, DebugDrawConfig{ false, false, false, false, false, false });
	world.AddAgent(platoonFormation);
	world.AddAgent(enemyFormation1);
	world.AddAgent(enemyFormation2);

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
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << mouse.x << "/" << mouse.y << std::endl;
				}
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
				//	newAgent->steeringManager->AddBehaviorGroup(new Arrive(), 1.0f);
				//	newAgent->steeringManager->AddBehaviorGroup(new Seperation(50.0f), 5.0f);
				//	newAgent->steeringManager->AddBehaviorGroup(new LookWhereYouAreGoing(), 1.0f);
				//	newAgent->target.position = glm::vec2(targetSprite.getPosition().x, targetSprite.getPosition().y);
				//	world.AddAgent(newAgent);
				//}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::R)
				{
					world.GetDebugInfo().debugRays = !world.GetDebugInfo().debugRays;
				}

				if (event.key.code == sf::Keyboard::F)
				{
					world.GetDebugInfo().debugFormation = !world.GetDebugInfo().debugFormation;
				}

				if (event.key.code == sf::Keyboard::V)
				{
					world.GetDebugInfo().debugVelocities = !world.GetDebugInfo().debugVelocities;
				}

				if (event.key.code == sf::Keyboard::O)
				{
					world.GetDebugInfo().debugOrientation = !world.GetDebugInfo().debugOrientation;
				}

				if (event.key.code == sf::Keyboard::S)
				{
					world.GetDebugInfo().debugRadius = !world.GetDebugInfo().debugRadius;
				}

				if (event.key.code == sf::Keyboard::P)
				{
					world.GetDebugInfo().debugPath = !world.GetDebugInfo().debugPath;
				}
			}
		}

		window.clear(sf::Color(174, 198, 207));
		
		// update
		world.Update(dt.asSeconds());

		// debug draw paths
		platoonPath.DrawDebug(window, world.GetDebugInfo());
		enemyPath1.DrawDebug(window, world.GetDebugInfo());
		enemyPath2.DrawDebug(window, world.GetDebugInfo());
		
		//draw
		platoonPath.Draw(window);
		world.Draw(window);

		window.display();
	}

	return 0;
}

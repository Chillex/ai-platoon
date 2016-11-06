#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Obstacle.h"
#include "Agent.h"

class World
{
public:
	World();
	World(std::vector<Obstacle>& obstacles, std::vector<Agent>& agents);
	~World();

	void AddObstacle(Obstacle& obstacle);
	void AddAgent(Agent& agent);

	std::vector<Obstacle>& GetObstacles();
	std::vector<Agent>& GetAgents();

	void Clear();
	void ClearObstalces();
	void ClearAgents();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window) const;
protected:
	std::vector<Obstacle> m_obstacles;
	std::vector<Agent> m_agents;
};

#endif

#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "DebugDrawConfig.h"

class Obstacle;
class Agent;

class World
{
public:
	World(std::vector<Obstacle*>& obstacles, std::vector<Agent*>& agents, DebugDrawConfig debugConf);
	~World();

	void AddObstacle(Obstacle* obstacle);
	void AddAgent(Agent* agent);

	const std::vector<Obstacle*>& GetObstacles() const;
	const std::vector<Agent*>& GetAgents() const;

	void Clear();
	void ClearObstalces();
	void ClearAgents();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window) const;

	void ToggleDebug();
	DebugDrawConfig& World::GetDebugInfo();

protected:
	std::vector<Obstacle*> m_obstacles;
	std::vector<Agent*> m_agents;
	DebugDrawConfig m_debugConf;
};

#endif

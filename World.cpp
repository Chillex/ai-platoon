#include "World.h"
#include "Obstacle.h"
#include "Agent.h"

World::World()
{
}

World::World(std::vector<Obstacle*>& obstacles, std::vector<Agent*>& agents)
	: m_obstacles(obstacles)
	, m_agents(agents)
{
}

World::~World()
{
}

void World::AddObstacle(Obstacle* obstacle)
{
	m_obstacles.push_back(obstacle);
}

void World::AddAgent(Agent* agent)
{
	m_agents.push_back(agent);
}

std::vector<Obstacle*>& World::GetObstacles()
{
	return m_obstacles;
}

std::vector<Agent*>& World::GetAgents()
{
	return m_agents;
}

void World::Clear()
{
	ClearObstalces();
	ClearAgents();
}

void World::ClearObstalces()
{
	m_obstacles.clear();
}

void World::ClearAgents()
{
	m_agents.clear();
}

void World::Update(float deltaTime)
{
	// update all obstacles
	for (std::vector<Obstacle*>::iterator it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}

	// update all agents
	for (std::vector<Agent*>::iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		(*it)->Update(deltaTime, *this);
	}
}

void World::Draw(sf::RenderWindow& window) const
{
	// draw all obstacles
	for (std::vector<Obstacle*>::const_iterator it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
	{
		(*it)->Draw(window);
	}

	// draw all agents
	for (std::vector<Agent*>::const_iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		(*it)->Draw(window);
	}
}

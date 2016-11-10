#include "Seperation.h"
#include "SteeringStruct.h"
#include "Agent.h"
#include "World.h"
#include <iostream>

Seperation::Seperation(float seperationRadius)
	: m_seperationRadius(seperationRadius)
{
}

Seperation::~Seperation()
{
}

Steering Seperation::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = SeperationVelocity(agent, world.GetAgents());

	return steering;
}

glm::vec2 Seperation::SeperationVelocity(const Agent& agent, const std::vector<Agent*>& worldAgents) const
{
	glm::vec2 velocity(0.0f);
	int neighbours = 0;

	for (std::vector<Agent*>::const_iterator it = worldAgents.begin(); it != worldAgents.end(); ++it)
	{
		const Agent& neighbour = *(*it);

		if(&neighbour == &agent)
			continue;

		glm::vec2 direction = agent.position - neighbour.position;
		float distance = glm::length(direction);

		if(distance < m_seperationRadius)
		{
			float strength = agent.maxLinearVelocity * (m_seperationRadius - distance) / m_seperationRadius;
			//float strength = std::min(5.0f / (distance * distance), agent.maxLinearVelocity);
			velocity += strength * glm::normalize(direction);
		}
	}

	return velocity;
}

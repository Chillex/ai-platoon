#include "Arrive.h"
#include "SteeringStruct.h"
#include "Agent.h"

Arrive::Arrive()
	: m_decelerationRadius(160.0f)
{
}

Arrive::~Arrive()
{
}

Steering Arrive::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = ArriveVelocity(agent) - agent.linearVelocity;

	return steering;
}

glm::vec2 Arrive::ArriveVelocity(const Agent& agent) const
{
	glm::vec2 desiredVelocity = agent.target.position - agent.position;
	float distance = glm::length(desiredVelocity);

	if (distance <= 0.0f)
		return desiredVelocity;

	if(distance < m_decelerationRadius)
	{
		desiredVelocity = glm::normalize(desiredVelocity) * agent.maxLinearVelocity * (distance / m_decelerationRadius);
	}
	else
	{
		desiredVelocity = glm::normalize(desiredVelocity) * agent.maxLinearVelocity;
	}

	return desiredVelocity;
}

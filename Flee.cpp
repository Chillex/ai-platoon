#include "Flee.h"
#include "SteeringStruct.h"
#include "Agent.h"

Flee::Flee()
{
}

Flee::~Flee()
{
}

Steering Flee::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = FleeVelocity(agent.target.position, agent);

	return steering;
}

glm::vec2 Flee::FleeVelocity(const glm::vec2 pos, const Agent& agent)
{
	glm::vec2 desiredVelocity(0.0f);

	glm::vec2 direction = agent.position - pos;
	if (glm::length(direction) > 0.0f)
		desiredVelocity = glm::normalize(direction) * agent.maxLinearVelocity;

	return desiredVelocity - agent.linearVelocity;
}

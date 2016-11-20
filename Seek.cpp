#include "Seek.h"
#include "SteeringStruct.h"
#include "Agent.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

Steering Seek::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = SeekVelocity(agent.target.position, agent);

	return steering;
}

glm::vec2 Seek::SeekVelocity(const glm::vec2 pos, const Agent& agent) const
{
	glm::vec2 desiredVelocity(0.0f);

	glm::vec2 direction = pos - agent.position;
	if (glm::length(direction) > 0.0f)
		desiredVelocity = glm::normalize(direction) * agent.maxLinearVelocity;

	return desiredVelocity - agent.linearVelocity;
}

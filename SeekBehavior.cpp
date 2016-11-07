#include "SeekBehavior.h"
#include "SteeringStruct.h"
#include "Agent.h"

SeekBehavior::SeekBehavior()
{
}

SeekBehavior::~SeekBehavior()
{
}

Steering SeekBehavior::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	glm::vec2 direction = agent.target - agent.position;
	if(glm::length(direction) > 0.0f)
	{
		glm::vec2 desiredVelocity = glm::normalize(direction) * agent.maxSpeed;
		steering.linear = desiredVelocity - agent.velocity;
	}

	return steering;
}

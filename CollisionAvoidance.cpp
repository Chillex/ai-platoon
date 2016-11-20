#include "CollisionAvoidance.h"
#include "SteeringStruct.h"
#include <vector>
#include "World.h"
#include "Agent.h"
#include <iostream>

CollisionAvoidance::CollisionAvoidance(float predictionTime)
	: Evade(nullptr, predictionTime)
{
}

CollisionAvoidance::~CollisionAvoidance()
{
}

Steering CollisionAvoidance::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = CollisionAvoidanceVelocity(agent, world);

	return steering;
}

glm::vec2 CollisionAvoidance::CollisionAvoidanceVelocity(const Agent& agent, const World& world)
{
	// mistakes from the book:
	// - before dot product missing
	// shortest time should be time to collison

	// 1. find the nearest collision
	float shortestCollisionTime = 2.5f;
	Agent* firstTarget = nullptr;
	float firstMinSeperation = 0.0f;
	float firstDistance = 0.0f;
	glm::vec2 firstRelativePosition(0.0f);
	glm::vec2 firstRelativeVelocity(0.0f);

	const std::vector<Agent*>& agents = world.GetAgents();
	for (std::vector<Agent*>::const_iterator it = agents.begin(); it != agents.end(); ++it)
	{
		Agent* target = (*it);

		if (target == &agent || target->team == agent.team || target->team < 0)
			continue;

		// calculate time to collision
		glm::vec2 relativePosition = target->position - agent.position;
		glm::vec2 relativeVelocity = target->linearVelocity - agent.linearVelocity;
		float relativeSpeed = glm::length(relativeVelocity);
		float timeToCollision = -glm::dot(relativePosition, relativeVelocity) / (relativeSpeed * relativeSpeed);

		// check if collision
		float distance = glm::length(relativePosition);
		float minSeperation = distance - relativeSpeed * timeToCollision;
		if (minSeperation > 2 * agent.sizeRadius)
			continue; // no collision

		// check if this is the shortest collision
		if(timeToCollision > 0.0f && timeToCollision < shortestCollisionTime)
		{
			shortestCollisionTime = timeToCollision;
			firstTarget = target;
			firstMinSeperation = minSeperation;
			firstDistance = distance;
			firstRelativePosition = relativePosition;
			firstRelativeVelocity = relativeVelocity;
		}
	}

	// 2. get the velocity
	if (firstTarget == nullptr)
		return glm::vec2(0.0f);

	if (firstMinSeperation <= 0.0f || firstDistance < 2 * agent.sizeRadius)
		return FleeVelocity(firstTarget->position, agent);
	else
		return EvadeVelocity(agent, firstTarget);
}

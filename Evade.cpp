#include "Evade.h"
#include "SteeringStruct.h"
#include "Agent.h"

Evade::Evade(Agent* target, float predictionTime)
	: m_target(target)
	, m_predictionTime(predictionTime)
{
}

Evade::~Evade()
{
}

Steering Evade::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = EvadeVelocity(agent, m_target) - agent.linearVelocity;

	return steering;
}

glm::vec2 Evade::EvadeVelocity(const Agent& agent, const Agent* targetAgent)
{
	float prediction = 0.0f;
	glm::vec2 direction = targetAgent->position - agent.position;
	float distance = glm::length(direction);

	float speed = glm::length(agent.linearVelocity);

	if (speed <= distance / m_predictionTime)
		prediction = m_predictionTime;
	else
		prediction = distance / speed;

	glm::vec2 target = targetAgent->position + targetAgent->linearVelocity * prediction;
	return FleeVelocity(target, agent);
}

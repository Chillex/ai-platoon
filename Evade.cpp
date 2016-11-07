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

	steering.linear = EvadeVelocity(agent) - agent.linearVelocity;

	return steering;
}

glm::vec2 Evade::EvadeVelocity(const Agent& agent)
{
	float prediction = 0.0f;
	glm::vec2 direction = m_target->position - agent.position;
	float distance = glm::length(direction);

	float speed = glm::length(agent.linearVelocity);

	if (speed <= distance / m_predictionTime)
		prediction = m_predictionTime;
	else
		prediction = distance / speed;

	glm::vec2 target = m_target->position + m_target->linearVelocity * prediction;
	return FleeVelocity(target, agent);
}

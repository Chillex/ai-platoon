#include "Persue.h"
#include "SteeringStruct.h"
#include "Agent.h"

Persue::Persue(Agent* target, float predictionTime)
	: m_target(target)
	, m_predictionTime(predictionTime)
{
}

Persue::~Persue()
{
}

Steering Persue::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = PersueVelocity(agent);

	return steering;
}

glm::vec2 Persue::PersueVelocity(const Agent& agent) const
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
	return SeekVelocity(target, agent);
}

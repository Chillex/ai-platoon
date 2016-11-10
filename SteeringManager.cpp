#include "SteeringManager.h"
#include "Agent.h"
#include "Seek.h"
#include "Arrive.h"
#include "LookWhereYouAreGoing.h"
#include <iostream>

SteeringManager::SteeringManager()
{
}


SteeringManager::~SteeringManager()
{
	for (std::vector<BlendedBehavior>::iterator it = m_behaviors.begin(); it != m_behaviors.end(); ++it)
	{
		delete it->behavior;
	}
}

void SteeringManager::AddBehavior(BaseBehavior* behavior, float value)
{
	BlendedBehavior b;
	b.behavior = behavior;
	b.value = value;
	m_behaviors.push_back(b);
}

Steering SteeringManager::GetSteering(Agent& agent, World& world)
{
	Steering overallSteering;
	overallSteering.SetZero();

	for(std::vector<BlendedBehavior>::iterator it = m_behaviors.begin(); it != m_behaviors.end(); ++it)
	{
		float value = it->value;
		if(value <= 0.0f)
			continue;

		Steering steering = it->behavior->GetSteering(agent, world);

		if (glm::length(steering.linear) > 0.0f)
		{
			overallSteering.linear += steering.linear * value;
		}

		if (steering.angular != 0.0f)
			overallSteering.angular += steering.angular * value;
	}

	overallSteering.TruncateLinear(agent.maxLinearAcceleration);
	overallSteering.TuncateAngular(agent.maxAngularAcceleration);

	return overallSteering;
}

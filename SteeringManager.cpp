#include "SteeringManager.h"



SteeringManager::SteeringManager()
{
}


SteeringManager::~SteeringManager()
{
}

Steering SteeringManager::GetSteering(glm::vec2& target, World& world)
{
	Steering overallSteering;

	for(std::map<BehaviorType::Enum, BaseBehavior>::iterator it = m_behaviors.begin(); it != m_behaviors.end(); ++it)
	{
		float value = m_behaviorValue[it->first];
		if(value <= 0.0f)
			continue;

		Steering steering = it->second.GetSteering(target, world);

		overallSteering.linear += steering.linear * value;
		overallSteering.angular += steering.angular * value;
	}

	return overallSteering;
}

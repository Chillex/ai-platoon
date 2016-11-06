#ifndef STEERING_MANAGER_H
#define STEERING_MANAGER_H

#include <map>
#include <glm.hpp>

#include "BehaviorType.h"
#include "World.h"
#include "BaseBehavior.h"

class SteeringManager
{
public:
	SteeringManager();
	~SteeringManager();

	Steering GetSteering(glm::vec2& target, World& world);

protected:
	std::map<BehaviorType::Enum, BaseBehavior> m_behaviors;
	std::map<BehaviorType::Enum, float> m_behaviorValue;
};

#endif

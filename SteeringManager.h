#ifndef STEERING_MANAGER_H
#define STEERING_MANAGER_H

#include <map>
#include <glm.hpp>

#include "BehaviorType.h"
#include "SteeringStruct.h"
#include "SeekBehavior.h"

class BaseBehavior;
class World;

class SteeringManager
{
public:
	SteeringManager();
	~SteeringManager();

	Steering GetSteering(Agent& agent, World& world);

protected:
	std::map<BehaviorType::Enum, BaseBehavior*> m_behaviors;
	std::map<BehaviorType::Enum, float> m_behaviorValue;
};

#endif

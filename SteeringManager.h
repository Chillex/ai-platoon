#ifndef STEERING_MANAGER_H
#define STEERING_MANAGER_H

#include <glm.hpp>
#include <vector>

#include "SteeringStruct.h"
#include "PriorityBlending.h"

class BaseBehavior;
class World;

class SteeringManager
{
public:
	SteeringManager();
	~SteeringManager();

	void AddBehaviorGroup(PriorityGroup& group);
	void AddBehavior(BaseBehavior* behavior, float value, int priority);
	Steering GetSteering(Agent& agent, World& world);

protected:
	std::vector<PriorityGroup> m_priorityGroups;
	float m_linearThreshhold;
	float m_angularThreshhold;
};

#endif

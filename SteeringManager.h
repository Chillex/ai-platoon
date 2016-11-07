#ifndef STEERING_MANAGER_H
#define STEERING_MANAGER_H

#include <glm.hpp>
#include <vector>

#include "SteeringStruct.h"
#include "BlendedBehavior.h"

class BaseBehavior;
class World;

class SteeringManager
{
public:
	SteeringManager();
	~SteeringManager();

	void AddBehavior(BaseBehavior* behavior, float value);
	Steering GetSteering(Agent& agent, World& world);

protected:
	std::vector<BlendedBehavior> m_behaviors;

};

#endif

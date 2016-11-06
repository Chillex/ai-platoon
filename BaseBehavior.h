#ifndef BASE_BEHAVIOR_H
#define BASE_BEHAVIOR_H

#include "SteeringManager.h"

struct Steering
{
	glm::vec2 linear;
	float angular;
};

class BaseBehavior
{
public:
	BaseBehavior();
	virtual ~BaseBehavior() = 0;

	virtual Steering GetSteering(glm::vec2& target, World& world) = 0;
};

#endif

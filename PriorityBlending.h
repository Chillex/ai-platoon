#ifndef PRIORITY_BLENDING_H
#define PRIORITY_BLENDING_H

#include "BaseBehavior.h"
#include <vector>

struct BlendedBehavior
{
	BaseBehavior* behavior;
	float value;
};

struct PriorityGroup
{
	std::vector<BlendedBehavior> behaviors;
	int priority;
};

#endif
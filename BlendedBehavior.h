#ifndef BLENDED_BEHAVIOR_H
#define BLENDED_BEHAVIOR_H

#include "BaseBehavior.h"

struct BlendedBehavior
{
	BaseBehavior* behavior;
	float value;
};

#endif
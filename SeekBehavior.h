#ifndef SEEK_BEHAVIOR_H
#define SEEK_BEHAVIOR_H

#include "BaseBehavior.h"

class SeekBehavior : public BaseBehavior
{
public:
	SeekBehavior();
	~SeekBehavior();

	virtual Steering GetSteering(Agent& agent, World& world) override;
};

#endif

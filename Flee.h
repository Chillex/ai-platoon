#ifndef FLEE_H
#define FLEE_H

#include "BaseBehavior.h"

class Flee : public BaseBehavior
{
public:
	Flee();
	~Flee();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 FleeVelocity(const glm::vec2 pos, const Agent& agent);
};

#endif

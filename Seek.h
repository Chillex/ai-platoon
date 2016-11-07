#ifndef SEEK_H
#define SEEK_H

#include "BaseBehavior.h"

class Seek : public BaseBehavior
{
public:
	Seek();
	~Seek();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 SeekVelocity(const glm::vec2 pos, const Agent& agent) const;
};

#endif

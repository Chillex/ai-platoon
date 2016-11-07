#ifndef ARRIVE_H
#define ARRIVE_H

#include "BaseBehavior.h"

class Arrive : public BaseBehavior
{
public:
	Arrive();
	~Arrive();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 ArriveVelocity(const Agent& agent) const;

protected:
	float m_decelerationRadius;
};

#endif

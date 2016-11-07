#ifndef LOOK_WHERE_YOU_ARE_GOING_H
#define LOOK_WHERE_YOU_ARE_GOING_H

#include "BaseBehavior.h"

class LookWhereYouAreGoing : public BaseBehavior
{
public:
	explicit LookWhereYouAreGoing(float tolerance, float decelerationRadius);
	~LookWhereYouAreGoing();

	virtual Steering GetSteering(Agent& agent, World& world) override;

protected:
	float m_tolarence;
	float m_decelerationRadius;

	float WrapAngle(float angle) const;
};

#endif

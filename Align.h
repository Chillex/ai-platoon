#ifndef ALIGN_H
#define ALIGN_H

#include "BaseBehavior.h"

class Align : public BaseBehavior
{
public:
	Align();
	~Align();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	float AlignVelocity(const Agent& agent, const float targetOrientation) const;
	float WrapAngle(float angle) const;

protected:
	float m_tolarence;
	float m_decelerationRadius;
};

#endif

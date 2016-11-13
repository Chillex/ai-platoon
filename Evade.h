#ifndef EVADE_H
#define EVADE_H

#include "Flee.h"

class Evade : public Flee
{
public:
	Evade(Agent* target, float predictionTime);
	~Evade();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 EvadeVelocity(const Agent& agent, const Agent* targetAgent);

protected:
	Agent* m_target;
	float m_predictionTime;
};

#endif

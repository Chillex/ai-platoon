#ifndef PERSUIT_H
#define PERSUIT_H

#include "Seek.h"

class Persue : public Seek
{
public:
	Persue(Agent* target, float predictionTime);
	~Persue();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 PersueVelocity(const Agent& agent) const;

protected:
	Agent* m_target;
	float m_predictionTime;
};

#endif

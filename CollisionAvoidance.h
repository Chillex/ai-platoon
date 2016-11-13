#ifndef COLLISION_AVOIDANCE_H
#define COLLISION_AVOIDANCE_H

#include "Evade.h"

class CollisionAvoidance : public Evade
{
public:
	CollisionAvoidance(float predictionTime);
	~CollisionAvoidance();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 CollisionAvoidanceVelocity(const Agent& agent, const World& world);
};

#endif

#ifndef OBSTACLE_AVOIDANCE_H
#define OBSTACLE_AVOIDANCE_H

#include "Seek.h"

class ObstacleAvoidance : public Seek
{
public:
	ObstacleAvoidance();
	~ObstacleAvoidance();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 ObstacleAvoidanceVelocity(const Agent& agent, const World& world) const;

	static glm::vec2 Intersects(const glm::vec2 a1, const glm::vec2 a2, const glm::vec2 b1, const glm::vec2 b2);
};

#endif

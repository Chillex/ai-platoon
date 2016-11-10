#ifndef SEPERATION_H
#define SEPERATION_H

#include "BaseBehavior.h"
#include <vector>

class Seperation : public BaseBehavior
{
public:
	explicit Seperation(float seperationRadius);
	~Seperation();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 SeperationVelocity(const Agent& agent, const std::vector<Agent*>& worldAgents) const;

protected:
	float m_seperationRadius;
};

#endif

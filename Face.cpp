#include "Face.h"
#include "SteeringStruct.h"
#include "Agent.h"


Face::Face()
{
}


Face::~Face()
{
}

Steering Face::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	glm::vec2 direction = agent.target.position - agent.position;
	float targetOrientation = glm::degrees(atan2(direction.y, direction.x));
	steering.angular = AlignVelocity(agent, targetOrientation);

	return steering;
}

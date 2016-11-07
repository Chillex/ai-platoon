#include "LookWhereYouAreGoing.h"
#include "SteeringStruct.h"
#include "Agent.h"

LookWhereYouAreGoing::LookWhereYouAreGoing()
{
}

LookWhereYouAreGoing::~LookWhereYouAreGoing()
{
}

Steering LookWhereYouAreGoing::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	float targetOrientation = glm::degrees(atan2(agent.linearVelocity.y, agent.linearVelocity.x));
	steering.angular = AlignVelocity(agent, targetOrientation);

	return steering;
}

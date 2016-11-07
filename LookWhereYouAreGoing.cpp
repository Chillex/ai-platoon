#include "LookWhereYouAreGoing.h"
#include "SteeringStruct.h"
#include "Agent.h"
#include <iostream>

LookWhereYouAreGoing::LookWhereYouAreGoing(float tolerance, float decelerationRadius)
	: m_tolarence(tolerance)
	, m_decelerationRadius(decelerationRadius)
{
}

LookWhereYouAreGoing::~LookWhereYouAreGoing()
{
}

Steering LookWhereYouAreGoing::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	float targetOrientation = glm::degrees(atan2(agent.velocity.y, agent.velocity.x)) + 90.0f;
	float rotation = WrapAngle(targetOrientation - agent.orientation);
	float rotationSize = abs(rotation);

	if (rotationSize > m_tolarence)
	{
		float targetRotation = agent.maxRotation;

		if (rotationSize <= m_decelerationRadius)
			targetRotation *= rotationSize / m_decelerationRadius;

		targetRotation *= rotation / rotationSize;

		steering.angular = targetRotation - agent.rotation; // maybe () / 0.1f is needed

		float angularAcceleration = abs(steering.angular);
		if (angularAcceleration > agent.maxAngularAcceleration)
			steering.angular *= agent.maxAngularAcceleration / angularAcceleration;
	}

	return steering;
}

float LookWhereYouAreGoing::WrapAngle(float angle) const
{
	angle = fmod(angle + 180.0f, 360.0f);

	if (angle < 0)
		angle += 360.0f;

	return angle - 180.0f;
}

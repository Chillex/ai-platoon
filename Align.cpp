#include "Align.h"
#include "SteeringStruct.h"
#include "Agent.h"

Align::Align()
	: m_tolarence(0.1f)
	, m_decelerationRadius(20.0f)
{
}


Align::~Align()
{
}

Steering Align::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.angular = AlignVelocity(agent, agent.target.orientation);

	return steering;
}

float Align::AlignVelocity(const Agent& agent, const float targetOrientation) const
{
	float velocity = 0.0f;

	float rotation = WrapAngle(targetOrientation - agent.orientation);
	float rotationSize = abs(rotation);

	if (rotationSize > m_tolarence)
	{
		float targetRotation = agent.maxAngularVelocity;

		if (rotationSize <= m_decelerationRadius)
			targetRotation *= rotationSize / m_decelerationRadius;

		targetRotation *= rotation / rotationSize;

		velocity = targetRotation - agent.angularVelocity; // maybe () / 0.1f is needed

		float angularAcceleration = abs(velocity);
		if (angularAcceleration > agent.maxAngularAcceleration)
			velocity *= agent.maxAngularAcceleration / angularAcceleration;
	}

	return velocity;
}

float Align::WrapAngle(float angle) const
{
	angle = fmod(angle + 180.0f, 360.0f);

	if (angle < 0)
		angle += 360.0f;

	return angle - 180.0f;
}

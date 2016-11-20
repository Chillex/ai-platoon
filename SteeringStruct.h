#ifndef STEERING_STRUCT_H
#define STEERING_STRUCT_H

#include <glm.hpp>

struct Steering
{
	glm::vec2 linear;
	float angular;

	void TruncateLinear(float maxForce)
	{
		float length = glm::length(linear);
		if (length > 0.0f && length > maxForce)
			linear = glm::normalize(linear) * maxForce;
	}

	void SetZero()
	{
		linear = glm::vec2(0.0f);
		angular = 0.0f;
	}

	void TuncateAngular(float maxAngularAcceleration)
	{
		if (abs(angular) > maxAngularAcceleration)
			angular *= maxAngularAcceleration / abs(angular);
	}

	bool IsAboveThreshhold(float linear, float angular) const
	{
		if (glm::length(this->linear) > linear || abs(this->angular) > angular)
			return true;

		return false;
	}
};

#endif
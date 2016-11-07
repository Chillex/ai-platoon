#ifndef TARGET_H
#define TARGET_H

#include <glm.hpp>

struct Target
{
	glm::vec2 position;
	float orientation;
	glm::vec2 linearVelocity;
};

#endif TARGET_H
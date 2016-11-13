#ifndef BASE_BEHAVIOR_H
#define BASE_BEHAVIOR_H

#include <glm.hpp>

struct Steering;
class Agent;
class World;

class BaseBehavior
{
public:
	BaseBehavior();
	virtual ~BaseBehavior();

	virtual Steering GetSteering(Agent& agent, World& world) = 0;
};

#endif

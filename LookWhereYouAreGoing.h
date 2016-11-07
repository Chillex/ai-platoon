#ifndef LOOK_WHERE_YOU_ARE_GOING_H
#define LOOK_WHERE_YOU_ARE_GOING_H

#include "Face.h"

class LookWhereYouAreGoing : public Face
{
public:
	LookWhereYouAreGoing();
	~LookWhereYouAreGoing();

	virtual Steering GetSteering(Agent& agent, World& world) override;
};

#endif

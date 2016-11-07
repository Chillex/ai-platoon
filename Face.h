#ifndef FACE_H
#define FACE_H

#include "Align.h"

class Face : public Align
{
public:
	Face();
	~Face();

	virtual Steering GetSteering(Agent& agent, World& world) override;
};

#endif

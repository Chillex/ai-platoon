#ifndef PATH_FOLLOWING_H
#define PATH_FOLLOWING_H

#include "Seek.h"

class Path;

class PathFollowing : public Seek
{
public:
	PathFollowing(const Path& path, bool loop);
	~PathFollowing();

	virtual Steering GetSteering(Agent& agent, World& world) override;
	glm::vec2 PathFollowingVelocity(const Path& path, const Agent& agent);

protected:
	const Path& m_path;
	const float m_predictionTime;
	int m_offset;
	bool m_loop;
};

#endif

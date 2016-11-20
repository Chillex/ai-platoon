#include "PathFollowing.h"
#include "SteeringStruct.h"
#include "Agent.h"
#include "Path.h"

PathFollowing::PathFollowing(const Path& path, bool loop)
	: m_path(path)
	, m_predictionTime(0.5f)
	, m_offset(1)
	, m_loop(loop)
{
}

PathFollowing::~PathFollowing()
{
}

Steering PathFollowing::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	steering.linear = PathFollowingVelocity(m_path, agent);

	return steering;
}

glm::vec2 PathFollowing::PathFollowingVelocity(const Path& path, const Agent& agent)
{
	// predict movement
	glm::vec2 futurePoint = agent.position + agent.linearVelocity * m_predictionTime;

	// get next waypoint of the path
	int closestWaypoint = path.GetClosestWaypoint(agent.position);
	glm::vec2 waypoint = path.GetNextWaypoint(closestWaypoint, m_offset);

	if (m_loop && path.IsLastWaypoint(closestWaypoint, m_offset))
		m_offset *= -1;

	// delegate to seek
	return SeekVelocity(waypoint, agent);
}

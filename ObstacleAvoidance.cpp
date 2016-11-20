#include "ObstacleAvoidance.h"
#include "SteeringStruct.h"
#include "Agent.h"
#include "World.h"
#include "Obstacle.h"

ObstacleAvoidance::ObstacleAvoidance()
{
}

ObstacleAvoidance::~ObstacleAvoidance()
{
}

Steering ObstacleAvoidance::GetSteering(Agent& agent, World& world)
{
	Steering steering;
	steering.SetZero();

	agent.CreateFeelers();
	steering.linear = ObstacleAvoidanceVelocity(agent, world);

	return steering;
}

glm::vec2 ObstacleAvoidance::ObstacleAvoidanceVelocity(const Agent& agent, const World& world) const
{
	const std::vector<Obstacle*> obstacles = world.GetObstacles();
	const std::vector<Line> feelers = agent.GetFeelers();

	glm::vec2 closestCollisionPoint(0.0f);
	float closestDistance = 100000.0f;

	for (std::vector<Line>::const_iterator feeler = feelers.begin(); feeler != feelers.end(); ++feeler)
	{
		Line closestWall(glm::vec2(0.0f), glm::vec2(0.0f));

		// check if the feeler collides with an obstacle
		for (std::vector<Obstacle*>::const_iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
		{
			sf::RectangleShape rect = (*obstacle)->shape;
			sf::Vector2f tl = rect.getTransform().transformPoint(0, 0);
			glm::vec2 topLeft(tl.x, tl.y);
			sf::Vector2f tr = rect.getTransform().transformPoint(rect.getSize().x, 0);
			glm::vec2 topRight(tr.x, tr.y);
			sf::Vector2f bl = rect.getTransform().transformPoint(0, rect.getSize().y);
			glm::vec2 bottomLeft(bl.x, bl.y);
			sf::Vector2f br = rect.getTransform().transformPoint(rect.getSize().x, rect.getSize().y);
			glm::vec2 bottomRight(br.x, br.y);

			glm::vec2 topIntersection = Intersects(feeler->first, feeler->second, topLeft, topRight);
			glm::vec2 rightIntersection = Intersects(feeler->first, feeler->second, topRight, bottomRight);
			glm::vec2 bottomIntersection = Intersects(feeler->first, feeler->second, bottomRight, bottomLeft);
			glm::vec2 leftIntersection = Intersects(feeler->first, feeler->second, bottomLeft, topLeft);

			if(topIntersection.x != 0.0f && topIntersection.y != 0.0f)
			{
				float distance = glm::distance(agent.position, topIntersection);
				if(distance < closestDistance)
				{
					closestDistance = distance;
					closestWall = Line(topLeft, topRight);
					closestCollisionPoint = topIntersection;
				}
			}

			if (rightIntersection.x != 0.0f && rightIntersection.y != 0.0f)
			{
				float distance = glm::distance(agent.position, rightIntersection);
				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestWall = Line(topRight, bottomRight);
					closestCollisionPoint = rightIntersection;
				}
			}

			if (bottomIntersection.x != 0.0f && bottomIntersection.y != 0.0f)
			{
				float distance = glm::distance(agent.position, bottomIntersection);
				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestWall = Line(bottomRight, bottomLeft);
					closestCollisionPoint = bottomIntersection;
				}
			}

			if (leftIntersection.x != 0.0f && leftIntersection.y != 0.0f)
			{
				float distance = glm::distance(agent.position, leftIntersection);
				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestWall = Line(bottomLeft, topLeft);
					closestCollisionPoint = leftIntersection;
				}
			}
		}

		// collision with this feeler
		if(glm::distance(closestWall.first, closestWall.second) != 0.0f)
		{
			// inside normal
			//glm::vec2 normal(-(closestWall.second.y - closestWall.first.y), closestWall.second.x - closestWall.first.x);
			// outside normal
			glm::vec2 normal(closestWall.second.y - closestWall.first.y, -(closestWall.second.x - closestWall.first.x));

			return SeekVelocity(closestCollisionPoint + glm::normalize(normal) * agent.sizeRadius * 3.0f, agent);
		}
	}

	return glm::vec2(0.0f);
}

// http://stackoverflow.com/questions/3746274/line-intersection-with-aabb-rectangle
glm::vec2 ObstacleAvoidance::Intersects(const glm::vec2 a1, const glm::vec2 a2, const glm::vec2 b1, const glm::vec2 b2)
{
	glm::vec2 b = a2 - a1;
	glm::vec2 d = b2 - b1;
	// http://johnblackburne.blogspot.co.at/2012/02/perp-dot-product.html
	float bDotdPerp = b.x * d.y - b.y * d.x;

	// both lines are parallel
	if (bDotdPerp == 0.0f)
		return glm::vec2(0.0f);

	glm::vec2 c = b1 - a1;
	float t = (c.x * d.y - c.y * d.x) / bDotdPerp;
	if(t < 0.0f || t > 1.0f)
		return glm::vec2(0.0f);

	float u = (c.x * b.y - c.y * b.x) / bDotdPerp;
	if (u < 0.0f || u > 1.0f)
		return glm::vec2(0.0f);

	return a1 + t * b;
}

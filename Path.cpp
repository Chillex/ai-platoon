#include "Path.h"
#include "DebugDrawConfig.h"

Path::Path()
	: color(sf::Color::Red)
{
}

Path::~Path()
{
}

void Path::GenerateRandomPath(int length)
{
	nodes.clear();

	for (int i = 0; i < length; ++i)
	{
		float factor = length * 0.6f;
		glm::vec2 p(rand() % static_cast<int>(1280 / factor), rand() % static_cast<int>(720 / factor));
		if(i > 0)
		{
			if(i > length / 2)
			{
				int r = rand() % 3;
				switch (r)
				{
				case 0:
					p.x *= -1.0f;
				case 1:
					p.y *= -1.0f;
				}
			}

			p.x += nodes[i - 1].x;
			p.y += nodes[i - 1].y;
		}

		nodes.push_back(glm::vec2(p.x, p.y));
	}
}

void Path::ClearPath()
{
	nodes.clear();
}

void Path::AddWaypoint(float x, float y)
{
	AddWaypoint(glm::vec2(x, y));
}

void Path::AddWaypoint(glm::vec2& waypoint)
{
	nodes.push_back(waypoint);
}

void Path::Draw(sf::RenderWindow& window) const
{
	sf::Texture pointTex;
	pointTex.loadFromFile("Assets/target.png");
	sf::Sprite point(pointTex, sf::IntRect(0, 0, 24, 24));
	point.setOrigin(12, 12);

	size_t last = nodes.size() - 1;
	point.setPosition(nodes[last].x, nodes[last].y);
	window.draw(point);
}

void Path::DrawDebug(sf::RenderWindow& window, DebugDrawConfig debugConf) const
{
	if(debugConf.debugPath)
	{
		sf::RectangleShape point(sf::Vector2f(10.0f, 10.0f));
		point.setOrigin(5.0f, 5.0f);
		point.setFillColor(color);

		for (int i = 0; i < nodes.size(); ++i)
		{
			point.setPosition(nodes[i].x, nodes[i].y);
			window.draw(point);

			if (i > 0)
			{
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(nodes[i - 1].x, nodes[i - 1].y), color),
					sf::Vertex(sf::Vector2f(nodes[i].x, nodes[i].y), color)
				};

				window.draw(line, 2, sf::Lines);
			}
		}
	}
}

int Path::GetClosestWaypoint(const glm::vec2& pos) const
{
	int closestIndex = -1;
	float closestDistance = 0.0f;

	for (int i = 0; i < nodes.size(); ++i)
	{
		float distance = glm::length(nodes[i] - pos);
		if (distance < closestDistance || closestIndex == -1)
		{
			closestIndex = i;
			closestDistance = distance;
		}
	}

	return closestIndex;
}

glm::vec2 Path::GetNextWaypoint(int waypoint, int offset) const
{
	if (nodes.size() < 2)
		return nodes[0];

	int nextWaypoint = waypoint + offset;
	if (nextWaypoint >= 0 && nextWaypoint < nodes.size())
		return nodes[nextWaypoint];

	if (offset > 0)
		return nodes[nodes.size() - 1];
	else
		return nodes[0];
}

glm::vec2 Path::GetClosestPointOnPath(const glm::vec2& pos) const
{
	if (nodes.size() < 2)
		return glm::vec2(0.0f);

	std::pair<glm::vec2, glm::vec2> lineSegment = GetClosestWayPointSegment(pos);
	
	return GetClosestPointOnLine(lineSegment.first, lineSegment.second, pos);
}

bool Path::IsLastWaypoint(int waypoint, int offset) const
{
	if (offset > 0.0f && waypoint == nodes.size() - 1)
		return true;

	if (offset < 0.0f && waypoint == 0)
		return true;

	return false;
}

glm::vec2 Path::GetClosestPointOnLine(const glm::vec2& start, const glm::vec2& end, const glm::vec2& pos) const
{
	float length = glm::length(start - end);

	if (length == 0.0f)
		return start;

	float t = glm::dot(pos - start, end - start) / length;

	if (t < 0.0f)
		return start;
	else if (t > 1.0f)
		return end;

	return start + t * (end - start);
}

std::pair<glm::vec2, glm::vec2> Path::GetClosestWayPointSegment(const glm::vec2& pos) const
{
	int closestWaypoint = GetClosestWaypoint(pos);

	if (closestWaypoint == 0)
		return std::make_pair(nodes[closestWaypoint], nodes[closestWaypoint + 1]);

	if (closestWaypoint == nodes.size() - 1)
		return std::make_pair(nodes[closestWaypoint - 1], nodes[closestWaypoint]);

	float distBefore = glm::length(nodes[closestWaypoint - 1] - pos);
	float distAfter = glm::length(nodes[closestWaypoint + 1] - pos);

	if (distBefore < distAfter)
		return std::make_pair(nodes[closestWaypoint - 1], nodes[closestWaypoint]);
	else
		return std::make_pair(nodes[closestWaypoint], nodes[closestWaypoint + 1]);
}

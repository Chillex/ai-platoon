#ifndef PATH_H
#define PATH_H

#include <vector>
#include <glm.hpp>
#include <SFML/Graphics.hpp>

class Path
{
public:
	Path();
	~Path();

	void GenerateRandomPath(int length);
	void ClearPath();
	void AddWaypoint(float x, float y);
	void AddWaypoint(glm::vec2& waypoint);

	void Draw(sf::RenderWindow& window);

	int GetClosestWaypoint(const glm::vec2& pos) const;
	glm::vec2 GetNextWaypoint(int waypoint, int offset) const;
	glm::vec2 GetClosestPointOnPath(const glm::vec2& pos) const;
	bool IsLastWaypoint(int waypoint, int offset) const;

protected:
	std::vector<glm::vec2> nodes;

	glm::vec2 GetClosestPointOnLine(const glm::vec2& start, const glm::vec2& end, const glm::vec2& pos) const;
	std::pair<glm::vec2, glm::vec2> GetClosestWayPointSegment(const glm::vec2& pos) const;
};

#endif

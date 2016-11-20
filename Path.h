#ifndef PATH_H
#define PATH_H

#include <vector>
#include <glm.hpp>
#include <SFML/Graphics.hpp>

struct DebugDrawConfig;

class Path
{
public:
	Path();
	~Path();

	void GenerateRandomPath(int length);
	void ClearPath();
	void AddWaypoint(float x, float y);
	void AddWaypoint(glm::vec2& waypoint);

	void Draw(sf::RenderWindow& window) const;
	void DrawDebug(sf::RenderWindow& window, DebugDrawConfig debugConf) const;

	int GetClosestWaypoint(const glm::vec2& pos) const;
	glm::vec2 GetNextWaypoint(int waypoint, int offset) const;
	glm::vec2 GetClosestPointOnPath(const glm::vec2& pos) const;
	bool IsLastWaypoint(int waypoint, int offset) const;
	
	sf::Color color;
protected:
	std::vector<glm::vec2> nodes;

	glm::vec2 GetClosestPointOnLine(const glm::vec2& start, const glm::vec2& end, const glm::vec2& pos) const;
	std::pair<glm::vec2, glm::vec2> GetClosestWayPointSegment(const glm::vec2& pos) const;
};

#endif

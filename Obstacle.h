#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle
{
public:
	Obstacle();
	Obstacle(float width, float height, float x, float y);
	Obstacle(sf::FloatRect data);
	~Obstacle();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window) const;

protected:
	sf::FloatRect m_data;
};

#endif

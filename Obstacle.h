#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle
{
public:
	Obstacle();
	Obstacle(float width, float height, float x, float y, float rotation);
	Obstacle(sf::FloatRect rect, float rotation, char* spritePath, sf::Vector2f spriteDimensions);
	~Obstacle();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window) const;

	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif

#include "Obstacle.h"
#include <iostream>


Obstacle::Obstacle()
	: Obstacle(sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, "Assets/obstacle.png", sf::Vector2f(140.0f, 140.0f))
{
}

Obstacle::Obstacle(float width, float height, float x, float y, float rotation)
	: Obstacle(sf::FloatRect(x, y, width, height), rotation, "Assets/obstacle.png", sf::Vector2f(140.0f, 140.0f))
{
}

Obstacle::Obstacle(sf::FloatRect info, float rotation, char* spritePath, sf::Vector2f spriteDimensions)
	: shape(sf::Vector2f(info.width, info.height))
	, sprite(texture, sf::IntRect(0, 0, spriteDimensions.x, spriteDimensions.y))
{
	shape.setOrigin(info.width * 0.5f, info.height * 0.5f);
	shape.setPosition(info.left, info.top);
	shape.setRotation(rotation);
	shape.setFillColor(sf::Color::Red);

	texture.loadFromFile(spritePath);
	texture.setSmooth(true);
	sprite.setOrigin(spriteDimensions.x * 0.5f, spriteDimensions.y * 0.5f);
	std::cout << info.width << "/" << spriteDimensions.x << " = " << info.width / spriteDimensions.x << std::endl;
	sprite.setScale(info.width / spriteDimensions.x, info.height / spriteDimensions.y);
	sprite.setPosition(info.left, info.top);
	sprite.setRotation(rotation);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(float deltaTime)
{
}

void Obstacle::Draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

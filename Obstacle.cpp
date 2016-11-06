#include "Obstacle.h"



Obstacle::Obstacle()
	: Obstacle(sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f))
{
}

Obstacle::Obstacle(float width, float height, float x, float y)
	: Obstacle(sf::FloatRect(x, y, width, height))
{
}

Obstacle::Obstacle(sf::FloatRect data)
	: m_data(data)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(float deltaTime)
{
}

void Obstacle::Draw(sf::RenderWindow& window) const
{
	sf::RectangleShape rect(sf::Vector2f(m_data.width, m_data.height));
	rect.setPosition(m_data.left, m_data.top);

	rect.setFillColor(sf::Color::Red);

	window.draw(rect);
}

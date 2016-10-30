#ifndef AGENT_H
#define AGENT_H

#include <SFML/Graphics.hpp>

class Agent
{
public:
	Agent(char* spritePath);
	~Agent();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

protected:
	float m_posX;
	float m_posY;

	sf::Texture m_spritesheet;
	sf::IntRect m_spriteRect;
	sf::Sprite m_sprite;
};

#endif

#include "Agent.h"

Agent::Agent(char* spritePath)
	: m_posX(0)
	, m_posY(0)
{
	m_spritesheet.loadFromFile(spritePath);

	m_spriteRect.width = 210;
	m_spriteRect.height = 360;
	m_spriteRect.left = 525;
	m_spriteRect.top = 0;

	m_sprite.setTexture(m_spritesheet);
	m_sprite.setTextureRect(m_spriteRect);
}

Agent::~Agent()
{
}

void Agent::Update(float deltaTime)
{
}

void Agent::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

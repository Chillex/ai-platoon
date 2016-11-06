#include "Agent.h"
#include <iostream>

Agent::Agent(char* spritePath)
	: m_position(100.0f, 100.0f)
	, m_velocity(0.0f, 0.0f)
	, m_orientation(180.0f)
	, m_rotation(0.0f)
	, m_target(m_position)
	, m_spriteRect(0, 0, 71, 128)
	, m_sprite(m_spritesheet, m_spriteRect)
{
	m_spritesheet.loadFromFile(spritePath);
	m_sprite.setScale(0.3f, 0.3f);
	m_sprite.setOrigin(m_spriteRect.width * 0.5f, m_spriteRect.height * 0.5f);
}

Agent::~Agent()
{
}

void Agent::Update(float deltaTime)
{
	m_position += m_velocity * deltaTime;
	m_orientation += m_rotation * deltaTime;

	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation(m_orientation);
}

void Agent::Draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

void Agent::SetTarget(glm::vec2 target)
{
	m_target = target;
}

glm::vec2 Agent::GetTarget() const
{
	return m_target;
}

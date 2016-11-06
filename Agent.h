#ifndef AGENT_H
#define AGENT_H

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "SteeringManager.h"

class Agent
{
public:
	Agent(char* spritePath);
	~Agent();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window) const;

	void SetTarget(glm::vec2 target);
	glm::vec2 GetTarget() const;

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;

	float m_orientation;
	float m_rotation;		// angular velocity

	glm::vec2 m_target;

	sf::Texture m_spritesheet;
	sf::IntRect m_spriteRect;
	sf::Sprite m_sprite;

	SteeringManager m_steeringManager;
};

#endif

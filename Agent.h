#ifndef AGENT_H
#define AGENT_H

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Target.h"

class World;
class SteeringManager;

class Agent
{
public:
	Agent(char* spritePath);
	Agent(char* spritePath, glm::vec2 position);
	~Agent();

	void Update(float deltaTime, World& world);
	void Draw(sf::RenderWindow& window) const;

	glm::vec2 Truncate(glm::vec2 vec, float max) const;
	float Truncate(float value, float max) const;

	glm::vec2 position;
	glm::vec2 linearVelocity;

	float orientation;
	float angularVelocity;

	float maxLinearVelocity;
	float maxLinearAcceleration;
	float maxAngularVelocity;
	float maxAngularAcceleration;

	Target target;

	SteeringManager* steeringManager;

protected:
	sf::Texture m_spritesheet;
	sf::IntRect m_spriteRect;
	sf::Sprite m_sprite;
};

#endif

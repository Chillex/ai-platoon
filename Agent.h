#ifndef AGENT_H
#define AGENT_H

#include <SFML/Graphics.hpp>
#include <glm.hpp>

class World;
class SteeringManager;

class Agent
{
public:
	Agent(char* spritePath);
	~Agent();

	void Update(float deltaTime, World& world);
	void Draw(sf::RenderWindow& window) const;

	glm::vec2 Truncate(glm::vec2 vec, float max);
	float Truncate(float value, float max);

	glm::vec2 position;
	glm::vec2 velocity;

	float orientation;
	float rotation;		// angular velocity

	float maxSpeed;
	float maxForce;
	float maxRotation;
	float maxAngularAcceleration;

	glm::vec2 target;

protected:
	sf::Texture m_spritesheet;
	sf::IntRect m_spriteRect;
	sf::Sprite m_sprite;

	SteeringManager* m_steeringManager;
};

#endif

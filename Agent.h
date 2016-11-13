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
	Agent(char* spritePath, glm::vec2 pos, float radius, sf::Color color, int maxFootprints, int team);
	~Agent();

	void Update(float deltaTime, World& world);
	void Draw(sf::RenderWindow& window) const;
	void DrawDebug(sf::RenderWindow& window) const;

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
	float sizeRadius;

	int team;

	Target target;

	SteeringManager* steeringManager;

protected:
	sf::Texture m_spritesheet;
	sf::IntRect m_spriteRect;
	sf::Sprite m_sprite;

	std::vector<glm::vec2> m_footprints;
	int m_maxFootprints;
	int m_lastFootprintIndex;
	float m_footpringSeperation;
	float m_nextFootpringTime;

	sf::Color m_color;
};

#endif

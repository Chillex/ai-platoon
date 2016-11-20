#ifndef AGENT_H
#define AGENT_H

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Target.h"
#include "DebugDrawConfig.h"

class World;
class SteeringManager;

typedef std::pair<glm::vec2, glm::vec2> Line;

class Agent
{
public:
	Agent();
	Agent(glm::vec2 pos, float radius, float lookAheadDistance, sf::Color color, int maxFootprints, int team);
	Agent(char* spritePath, glm::vec2 pos, float radius, float lookAheadDistance, sf::Color color, int maxFootprints, int team);
	virtual ~Agent();

	virtual void Update(float deltaTime, World& world);
	virtual void Draw(sf::RenderWindow& window) const;
	virtual void DrawDebug(sf::RenderWindow& window, DebugDrawConfig debugConf) const;

	glm::vec2 Truncate(glm::vec2 vec, float max) const;
	float Truncate(float value, float max) const;

	void CreateFeelers();
	const std::vector<Line> GetFeelers() const;

	const sf::Color& GetColor() const;

	glm::vec2 position;
	glm::vec2 linearVelocity;
	float orientation;
	float angularVelocity;
	float maxLinearVelocity;
	float maxLinearAcceleration;
	float maxAngularVelocity;
	float maxAngularAcceleration;

	float sizeRadius;
	float lookAheadDistance;

	int team;

	Target target;

	SteeringManager* steeringManager;

protected:
	sf::Texture m_spritesheet;
	sf::IntRect m_spriteRect;
	sf::Sprite m_sprite;

	std::vector<Line> m_feelers;

	std::vector<glm::vec2> m_footprints;
	int m_maxFootprints;
	int m_lastFootprintIndex;
	float m_footpringSeperation;
	float m_nextFootpringTime;

	sf::Color m_color;
};

#endif

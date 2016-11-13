#include "Agent.h"
#include "SteeringStruct.h"
#include "SteeringManager.h"

Agent::Agent(char* spritePath)
	: Agent(spritePath, glm::vec2(100.0f), 40.0f, sf::Color::White, 0, 0)
{
	
}

Agent::Agent(char* spritePath, glm::vec2 pos, float radius, sf::Color color, int maxFootprints, int team)
	: position(pos)
	, linearVelocity(0.0f, 0.0f)
	, orientation(0.0f)
	, angularVelocity(0.0f)
	, maxLinearVelocity(150.0f)
	, maxLinearAcceleration(100.0f)
	, maxAngularVelocity(glm::degrees(2.0f))
	, maxAngularAcceleration(glm::degrees(4.0f))
	, sizeRadius(radius)
	, team(team)
	, target({ position, orientation })
	, m_spriteRect(0, 0, 32, 64)
	, m_sprite(m_spritesheet, m_spriteRect)
	, m_maxFootprints(maxFootprints)
	, m_lastFootprintIndex(-1)
	, m_footpringSeperation(0.5f)
	, m_nextFootpringTime(0.0f)
	, m_color(color)
{
	m_spritesheet.loadFromFile(spritePath);
	m_sprite.setOrigin(m_spriteRect.width * 0.5f, m_spriteRect.height * 0.5f);
	m_sprite.setColor(m_color);

	steeringManager = new SteeringManager();
}

Agent::~Agent()
{
	delete steeringManager;
}

void Agent::Update(float deltaTime, World& world)
{
	// move and rotate agent agent
	position += linearVelocity * deltaTime;
	orientation += angularVelocity * deltaTime;

	// calculate linearVelocity
	Steering steering = steeringManager->GetSteering(*this, world);

	linearVelocity = Truncate(linearVelocity + steering.linear * deltaTime, maxLinearVelocity);
	angularVelocity = Truncate(angularVelocity + steering.angular * deltaTime, maxAngularVelocity);

	// set sprite data
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(orientation + 90.0f); // +90.0f because weird SFML stuff

	// set footprint data
	if(m_maxFootprints > 0)
	{
		m_nextFootpringTime -= deltaTime;
		if (m_nextFootpringTime <= 0.0f)
		{
			if (m_footprints.size() < m_maxFootprints)
			{
				m_footprints.push_back(position);
			}
			else
			{
				++m_lastFootprintIndex;
				if (m_lastFootprintIndex >= m_maxFootprints)
					m_lastFootprintIndex = 0;

				m_footprints[m_lastFootprintIndex] = position;
			}

			m_nextFootpringTime = m_footpringSeperation;
		}
	}
}

void Agent::Draw(sf::RenderWindow& window) const
{
	// draw the image
	window.draw(m_sprite);
}

void Agent::DrawDebug(sf::RenderWindow& window) const
{
	sf::Vector2f pos(position.x, position.y);

	// draw velocity
	glm::vec2 endVel = position + linearVelocity;
	sf::Vertex velocityLine[] =
	{
		sf::Vertex(pos, sf::Color::Blue),
		sf::Vertex(sf::Vector2f(endVel.x, endVel.y), sf::Color::Blue),
	};
	window.draw(velocityLine, 2, sf::Lines);

	// draw orientation
	float x = cos(glm::radians(orientation));
	float y = sin(glm::radians(orientation));
	glm::vec2 orientation(x, y);
	glm::vec2 endOrientation = position + orientation * 50.0f;
	sf::Vertex orientationLine[] =
	{
		sf::Vertex(pos, sf::Color::Magenta),
		sf::Vertex(sf::Vector2f(endOrientation.x, endOrientation.y), sf::Color::Magenta),
	};
	window.draw(orientationLine, 2, sf::Lines);

	// draw size radius
	sf::CircleShape size(sizeRadius);
	size.setOrigin(sizeRadius, sizeRadius);
	size.setFillColor(sf::Color::Transparent);
	size.setOutlineColor(m_color);
	size.setOutlineThickness(2.0f);
	size.setPosition(pos);
	window.draw(size);

	// draw footprints
	if(m_maxFootprints > 0)
	{
		sf::CircleShape footprint(2.5f);
		footprint.setFillColor(m_color);
		footprint.setOrigin(2.5f, 2.5f);
		for (int i = 0; i < m_footprints.size(); ++i)
		{
			footprint.setPosition(sf::Vector2f(m_footprints[i].x, m_footprints[i].y));
			window.draw(footprint);
		}
	}
}

glm::vec2 Agent::Truncate(glm::vec2 vec, float max) const
{
	if(glm::length(vec) > 0.0f)
	{
		float factor = max / glm::length(vec);
		factor = factor < 1.0f ? factor : 1.0f;
		vec *= abs(factor);
	}
	
	return vec;
}

float Agent::Truncate(float value, float max) const
{
	if(value > 0.0f)
	{
		float factor = max / value;
		factor = factor < 1.0f ? factor : 1.0f;
		value *= abs(factor);
	}

	return value;
}

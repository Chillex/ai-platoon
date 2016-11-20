#include "Agent.h"
#include "SteeringStruct.h"
#include "SteeringManager.h"

Agent::Agent()
	: Agent(glm::vec2(100.0f), 25.0f, 100.0f, sf::Color::Transparent, 0, -1)
{
	
}

Agent::Agent(glm::vec2 pos, float radius, float lookAheadDistance, sf::Color color, int maxFootprints, int team)
	: position(pos)
	, linearVelocity(0.0f, 0.0f)
	, orientation(0.0f)
	, angularVelocity(0.0f)
	, maxLinearVelocity(150.0f)
	, maxLinearAcceleration(100.0f)
	, maxAngularVelocity(glm::degrees(2.0f))
	, maxAngularAcceleration(glm::degrees(4.0f))
	, sizeRadius(radius)
	, lookAheadDistance(lookAheadDistance)
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
	steeringManager = new SteeringManager();
}

Agent::Agent(char* spritePath, glm::vec2 pos, float radius, float lookAheadDistance, sf::Color color, int maxFootprints, int team)
	: Agent(pos, radius, lookAheadDistance, color, maxFootprints, team)
{
	m_spritesheet.loadFromFile(spritePath);
	m_spritesheet.setSmooth(true);
	m_sprite.setOrigin(m_spriteRect.width * 0.5f, m_spriteRect.height * 0.5f);
	m_sprite.setColor(m_color);
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

void Agent::DrawDebug(sf::RenderWindow& window, DebugDrawConfig debugConf) const
{
	sf::Vector2f pos(position.x, position.y);

	// draw central ray and whiskers
	if (debugConf.debugRays)
	{
		for (std::vector<Line>::const_iterator it = m_feelers.begin(); it != m_feelers.end(); ++it)
		{
			sf::Vertex feeler[] =
			{
				sf::Vertex(sf::Vector2f(it->first.x, it->first.y), sf::Color::Cyan),
				sf::Vertex(sf::Vector2f(it->second.x, it->second.y), sf::Color::Cyan),
			};
			window.draw(feeler, 2, sf::Lines);
		}
	}
	
	// draw velocity
	if(debugConf.debugVelocities)
	{
		glm::vec2 endVel = position + linearVelocity;
		sf::Vertex velocityLine[] =
		{
			sf::Vertex(pos, sf::Color::Blue),
			sf::Vertex(sf::Vector2f(endVel.x, endVel.y), sf::Color::Blue),
		};
		window.draw(velocityLine, 2, sf::Lines);
	}

	// draw orientation
	if(debugConf.debugOrientation)
	{
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
	}

	// draw size radius
	if(debugConf.debugRadius)
	{
		sf::CircleShape size(sizeRadius);
		size.setOrigin(sizeRadius, sizeRadius);
		size.setFillColor(sf::Color::Transparent);
		size.setOutlineColor(m_color);
		size.setOutlineThickness(2.0f);
		size.setPosition(pos);
		window.draw(size);
	}

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

void Agent::CreateFeelers()
{
	m_feelers.clear();

	// central ray
	Line central = std::make_pair(position, position + glm::normalize(linearVelocity) * lookAheadDistance);

	// whiskers
	float velocityAngle = atan2(linearVelocity.y, linearVelocity.x);
	float leftWhiskersAngle = velocityAngle - glm::radians(35.0f);
	float rightWhiskersAngle = velocityAngle + glm::radians(35.0f);

	// left whiskers
	glm::vec2 leftWhiskersDirection(cos(leftWhiskersAngle), sin(leftWhiskersAngle));
	Line leftWhiskers = std::make_pair(position, position + glm::normalize(leftWhiskersDirection) * lookAheadDistance * 0.5f);

	// right whiskers
	glm::vec2 rightWhiskersDirection(cos(rightWhiskersAngle), sin(rightWhiskersAngle));
	Line rightWhiskers = std::make_pair(position, position + glm::normalize(rightWhiskersDirection) * lookAheadDistance * 0.5f);

	m_feelers.push_back(central);
	m_feelers.push_back(leftWhiskers);
	m_feelers.push_back(rightWhiskers);
}

const std::vector<Line> Agent::GetFeelers() const
{
	return m_feelers;
}

const sf::Color& Agent::GetColor() const
{
	return m_color;
}

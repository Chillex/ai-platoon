#include "Agent.h"
#include "SteeringStruct.h"
#include "SteeringManager.h"

Agent::Agent(char* spritePath)
	: Agent(spritePath, glm::vec2(100.0f))
{
	
}

Agent::Agent(char* spritePath, glm::vec2 pos)
	: position(pos)
	, linearVelocity(0.0f, 0.0f)
	, orientation(0.0f)
	, angularVelocity(0.0f)
	, maxLinearVelocity(200.0f)
	, maxLinearAcceleration(0.1f)
	, maxAngularVelocity(150.0f)
	, maxAngularAcceleration(3.0f)
	, target({ position, orientation })
	, m_spriteRect(0, 0, 32, 64)
	, m_sprite(m_spritesheet, m_spriteRect)
{
	m_spritesheet.loadFromFile(spritePath);
	m_sprite.setOrigin(m_spriteRect.width * 0.5f, m_spriteRect.height * 0.5f);

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

	linearVelocity = Truncate(linearVelocity + steering.linear, maxLinearVelocity);
	angularVelocity = Truncate(angularVelocity + steering.angular, maxAngularVelocity);

	// set sprite data
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(orientation + 90.0f); // +90.0f because weird SFML stuff
}

void Agent::Draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
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

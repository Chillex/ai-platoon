#include "Agent.h"
#include "SteeringStruct.h"
#include "SteeringManager.h"
#include <iostream>

Agent::Agent(char* spritePath)
	: position(100.0f, 100.0f)
	, velocity(0.0f, 0.0f)
	, orientation(90.0f)
	, rotation(0.0f)
	, maxSpeed(150.0f)
	, maxForce(0.1f)
	, maxRotation(150.0f)
	, maxAngularAcceleration(3.0f)
	, target(position)
	, m_spriteRect(0, 0, 71, 128)
	, m_sprite(m_spritesheet, m_spriteRect)
{
	m_spritesheet.loadFromFile(spritePath);
	m_sprite.setScale(0.5f, 0.5f);
	m_sprite.setOrigin(m_spriteRect.width * 0.5f, m_spriteRect.height * 0.5f);

	m_steeringManager = new SteeringManager();
}

Agent::~Agent()
{
	delete m_steeringManager;
}

void Agent::Update(float deltaTime, World& world)
{
	// move and rotate agent agent
	position += velocity * deltaTime;
	orientation += rotation * deltaTime;

	// calculate velocity
	Steering steering = m_steeringManager->GetSteering(*this, world);

	velocity = Truncate(velocity + steering.linear, maxSpeed);
	rotation = Truncate(rotation + steering.angular, maxRotation);

	// set sprite data
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(orientation);
}

void Agent::Draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

glm::vec2 Agent::Truncate(glm::vec2 vec, float max)
{
	if(glm::length(vec) > 0.0f)
	{
		float factor = max / glm::length(vec);
		factor = factor < 1.0f ? factor : 1.0f;
		vec *= abs(factor);
	}
	
	return vec;
}

float Agent::Truncate(float value, float max)
{
	if(value > 0.0f)
	{
		float factor = max / value;
		factor = factor < 1.0f ? factor : 1.0f;
		value *= abs(factor);
	}

	return value;
}

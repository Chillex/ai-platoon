#include "Formation.h"

Formation::Formation(std::vector<Agent*> agents, std::vector<glm::vec2> positionOffsets, std::vector<float> orientationOffset)
	: Agent()
	, m_agents(agents)
	, m_positionOffsets(positionOffsets)
	, m_orientationOffsets(orientationOffset)
	, m_formationSpeed(maxLinearVelocity)
	, m_offsetThreshhold(200.0f)
{
	maxAngularVelocity = glm::degrees(0.75f);
}

Formation::~Formation()
{
}

void Formation::Update(float deltaTime, World& world)
{
	// throttle the speed if agents are behind
	float totalOffset = GetTotalAgentOffset();
	if(totalOffset >= m_offsetThreshhold * 2.0f)
		maxLinearVelocity = 0.0f;
	else if(totalOffset >= m_offsetThreshhold)
		maxLinearVelocity = m_formationSpeed * 0.5f;
	else
		maxLinearVelocity = m_formationSpeed;

	Agent::Update(deltaTime, world);

	float forwardX = cos(glm::radians(orientation));
	float forwardY = sin(glm::radians(orientation));
	glm::vec2 forward = glm::normalize(glm::vec2(-forwardX, -forwardY));
	glm::vec2 right(forward.y, -forward.x);

	for (int i = 0; i < m_agents.size(); ++i)
	{
		glm::vec2 offset = forward * m_positionOffsets[i].y + right * m_positionOffsets[i].x;
		m_agents[i]->target.position = position + offset;
		m_agents[i]->target.orientation = orientation + m_orientationOffsets[i];
	}
}

void Formation::Draw(sf::RenderWindow& window) const
{
}

void Formation::DrawDebug(sf::RenderWindow& window, DebugDrawConfig debugConf) const
{
	if (!debugConf.debugFormation)
		return;

	sf::CircleShape formation(10.0f);
	formation.setOrigin(10.0f, 10.0f);
	formation.setPosition(sf::Vector2f(position.x, position.y));
	formation.setFillColor(sf::Color::Black);
	window.draw(formation);

	formation.setRadius(10.0f);
	formation.setOrigin(10.f, 10.f);

	float forwardX = cos(glm::radians(orientation));
	float forwardY = sin(glm::radians(orientation));
	glm::vec2 forward = glm::normalize(glm::vec2(-forwardX, -forwardY));
	glm::vec2 right(forward.y, -forward.x);

	for (int i = 0; i < m_agents.size(); ++i)
	{
		glm::vec2 offset = forward * m_positionOffsets[i].y + right * m_positionOffsets[i].x;
		glm::vec2 slot = position + offset;
		formation.setPosition(sf::Vector2f(slot.x, slot.y));
		formation.setFillColor(m_agents[i]->GetColor());
		window.draw(formation);
	}

	//glm::vec2 center = GetFormationCenter();
	//formation.setFillColor(sf::Color::Yellow);
	//formation.setPosition(sf::Vector2f(center.x, center.y));
	//window.draw(formation);
}

void Formation::SetFormationSpeed(float speed)
{
	m_formationSpeed = speed;
	maxLinearVelocity = speed;
}

glm::vec2 Formation::GetFormationCenter() const
{
	glm::vec2 sum(0.0f);
	for (std::vector<Agent*>::const_iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		sum += (*it)->position;
	}

	return sum / static_cast<float>(m_agents.size());
}

float Formation::GetTotalAgentOffset() const
{
	float sum = 0.0f;
	for (std::vector<Agent*>::const_iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		sum += glm::length((*it)->position - (*it)->target.position);
	}

	return sum;
}

#ifndef FORMATION_H
#define FORMATION_H

#include "Agent.h"

class Formation : public Agent
{
public:
	Formation(std::vector<Agent*> agents, std::vector<glm::vec2> positionOffsets, std::vector<float> orientationOffset);
	~Formation();

	virtual void Update(float deltaTime, World& world) override;
	virtual void Draw(sf::RenderWindow& window) const override;
	virtual void DrawDebug(sf::RenderWindow& window, DebugDrawConfig debugConf) const override;

	void SetFormationSpeed(float speed);

protected:
	std::vector<Agent*> m_agents;
	std::vector<glm::vec2> m_positionOffsets;
	std::vector<float> m_orientationOffsets;
	float m_formationSpeed;
	float m_offsetThreshhold;

	glm::vec2 GetFormationCenter() const;
	float GetTotalAgentOffset() const;
};

#endif

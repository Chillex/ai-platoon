#include "SteeringManager.h"
#include "LookWhereYouAreGoing.h"
#include "Agent.h"


SteeringManager::SteeringManager()
{
	// SEEK
	m_behaviors.insert(std::make_pair(BehaviorType::SEEK, new SeekBehavior()));
	m_behaviorValue.insert(std::make_pair(BehaviorType::SEEK, 1.0f));

	// LOOK WHERE YOU ARE GOING
	m_behaviors.insert(std::make_pair(BehaviorType::LOOK_WHERE_YOU_ARE_GOING, new LookWhereYouAreGoing(0.1f, 20.0f)));
	m_behaviorValue.insert(std::make_pair(BehaviorType::LOOK_WHERE_YOU_ARE_GOING, 1.0f));
}


SteeringManager::~SteeringManager()
{
}

Steering SteeringManager::GetSteering(Agent& agent, World& world)
{
	Steering overallSteering;
	overallSteering.SetZero();

	for(std::map<BehaviorType::Enum, BaseBehavior*>::iterator it = m_behaviors.begin(); it != m_behaviors.end(); ++it)
	{
		float value = m_behaviorValue[it->first];
		if(value <= 0.0f)
			continue;

		Steering steering = it->second->GetSteering(agent, world);

		overallSteering.linear += steering.linear * value;
		overallSteering.angular += steering.angular * value;
	}

	overallSteering.TruncateLinear(agent.maxForce);
	overallSteering.TuncateAngular(agent.maxAngularAcceleration);
	return overallSteering;
}

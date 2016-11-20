#include "SteeringManager.h"
#include "Agent.h"

SteeringManager::SteeringManager()
	: m_linearThreshhold(0.1f)
	, m_angularThreshhold(0.1f)
{
}


SteeringManager::~SteeringManager()
{
	for (std::vector<PriorityGroup>::iterator it = m_priorityGroups.begin(); it != m_priorityGroups.end(); ++it)
	{
		for (std::vector<BlendedBehavior>::iterator b = it->behaviors.begin(); b != it->behaviors.end(); ++b)
		{
			delete b->behavior;
		}
	}
}

void SteeringManager::AddBehaviorGroup(PriorityGroup& group)
{
	m_priorityGroups.push_back(group);

	// sort the groups by priority
	std::sort(m_priorityGroups.begin(), m_priorityGroups.end(), 
		[](PriorityGroup const &a, PriorityGroup const &b)
		{
			return a.priority < b.priority;
		}
	);
}

void SteeringManager::AddBehavior(BaseBehavior* behavior, float value, int priority)
{
	BlendedBehavior b;
	b.behavior = behavior;
	b.value = value;

	m_priorityGroups[priority].behaviors.push_back(b);
}

Steering SteeringManager::GetSteering(Agent& agent, World& world)
{
	Steering overallSteering;
	overallSteering.SetZero();

	for (std::vector<PriorityGroup>::iterator group = m_priorityGroups.begin(); group != m_priorityGroups.end(); ++group)
	{
		Steering groupSteering;
		groupSteering.SetZero();

		for (std::vector<BlendedBehavior>::iterator it = group->behaviors.begin(); it != group->behaviors.end(); ++it)
		{
			float value = it->value;
			if (value <= 0.0f)
				continue;

			Steering behaviorSteering = it->behavior->GetSteering(agent, world);

			if (glm::length(behaviorSteering.linear) > 0.0f)
			{
				groupSteering.linear += behaviorSteering.linear * value;
			}

			if (behaviorSteering.angular != 0.0f)
				groupSteering.angular += behaviorSteering.angular * value;
		}

		if(groupSteering.IsAboveThreshhold(m_linearThreshhold, m_angularThreshhold))
		{
			overallSteering = groupSteering;
			break;
		}
	}

	overallSteering.TruncateLinear(agent.maxLinearAcceleration);
	overallSteering.TuncateAngular(agent.maxAngularAcceleration);

	return overallSteering;
}

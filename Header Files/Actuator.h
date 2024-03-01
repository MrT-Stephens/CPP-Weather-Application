#pragma once

#include <string>

enum class ActuatorState
{
	AlreadyTriggered,
	Off,
	On
};

enum class ActuatorTriggerType
{
	LessThan,
	GreaterThan,
	EqualTo,
	NotEqualTo
};

template <typename T>
class Actuator
{
private:
	bool m_AlreadyTriggered = false;
	T m_TriggerValue;
	std::string m_Name;
	ActuatorState m_State;
	ActuatorTriggerType m_TriggerType;
public:
	Actuator(const std::string& name, ActuatorTriggerType trigger_type, T trigger_value)
		: m_Name(name), m_State(ActuatorState::Off), m_TriggerValue(trigger_value), m_TriggerType(trigger_type)
	{
	}

	void SetState(ActuatorState state)
	{
		m_State = state;
	}

	ActuatorState GetState() const
	{
		return m_State;
	}

	std::string GetName() const
	{
		return m_Name;
	}

	T GetTriggerValue() const
	{
		return m_TriggerValue;
	}

	ActuatorState CheckTrigger(T value)
	{
		ActuatorState state = ActuatorState::Off;

		switch (m_TriggerType)
		{
		case ActuatorTriggerType::LessThan:
		{
			if (value < m_TriggerValue)
			{
				state = (m_AlreadyTriggered ? ActuatorState::AlreadyTriggered : ActuatorState::On);
				m_AlreadyTriggered = true;
			}
			else
			{
				m_AlreadyTriggered = false;
				state = ActuatorState::Off;
			}

			break;
		}
		case ActuatorTriggerType::GreaterThan:
		{
			if (value > m_TriggerValue)
			{
				state = (m_AlreadyTriggered ? ActuatorState::AlreadyTriggered : ActuatorState::On);
				m_AlreadyTriggered = true;
			}
			else
			{
				m_AlreadyTriggered = false;
				state = ActuatorState::Off;
			}

			break;
		}
		case ActuatorTriggerType::EqualTo:
		{
			if (value == m_TriggerValue)
			{
				state = (m_AlreadyTriggered ? ActuatorState::AlreadyTriggered : ActuatorState::On);
				m_AlreadyTriggered = true;
			}
			else
			{
				m_AlreadyTriggered = false;
				state = ActuatorState::Off;
			}

			break;
		}
		case ActuatorTriggerType::NotEqualTo:
		{
			if (value != m_TriggerValue)
			{
				state = (m_AlreadyTriggered ? ActuatorState::AlreadyTriggered : ActuatorState::On);
				m_AlreadyTriggered = true;
			}
			else
			{
				m_AlreadyTriggered = false;
				state = ActuatorState::Off;
			}

			break;
		}
		default:
			return ActuatorState::Off;
		}

		return state;
	}
};
#pragma once

#include <string>

/// <summary>
/// The state of the actuator.
/// </summary>
enum class ActuatorState
{
	AlreadyTriggered,
	Off,
	On
};

/// <summary>
/// The type of trigger for the actuator.
/// This is used to determine how the actuator will be triggered based on the value.
/// </summary>
enum class ActuatorTriggerType
{
	LessThan,
	GreaterThan,
	EqualTo,
	NotEqualTo
};

/// <summary>
/// The actuator class allows for the creation of an actuator which can be triggered based on a value of any type.
/// </summary>
/// <typeparam name="T"> The type for the trigger value. </typeparam>
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
	/// <summary>
	/// Initializes a new instance of the <see cref="Actuator"/> class.
	/// </summary>
	/// <param name="name"> Name of the actuator. </param>
	/// <param name="trigger_type"> The type of conditional trigger. </param>
	/// <param name="trigger_value"> The value which it will trigger at. </param>
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

	/// <summary>
	/// Checks the trigger based on the value.
	/// This will return the state of the actuator based on the value.
	/// If the actuator has already been triggered, it will return 'AlreadyTriggered'.
	/// If the actuator has not been triggered, it will return 'On'.
	/// If the actuator is not triggered, it will return 'Off'.
	/// </summary>
	/// <param name="value"> The current sensor value. </param>
	/// <returns> The current actuator state. </returns>
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
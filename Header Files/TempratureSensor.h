#pragma once

#include "../Header Files/Sensor.h"

/// <summary>
/// Temprature sensor class
/// Inherited from Sensor class
/// </summary>
class TempratureSensor : public Sensor<float, float>
{
private:
	bool m_Add = true;
	int32_t m_Min, m_Max;
public:
	/// <summary>
	/// Initalizes a new instance of <see cref="TempratureSensor"/> class.
	/// Names the sensor as "Temprature"
	/// </summary>
	/// <param name="min"> The minimum temprature value that can be simulated. </param>
	/// <param name="max"> The maximum temprature value that can be simulated. </param>
	TempratureSensor(int32_t min = -10, int32_t max = 30)
		: Sensor("Temprature"), m_Min(min), m_Max(max)
	{
		std::srand(std::time(nullptr));
	}

	/// <summary>
	/// Reads the temprature value from the sensor.
	/// The value is simulated by adding or subtracting a random value from the previous value.
	/// </summary>
	/// <returns></returns>
	float Read() override
	{
		float random = (float)rand() / (float)RAND_MAX;
		m_PreviousValue = m_Add ? m_PreviousValue + random : m_PreviousValue - random;

		if (m_PreviousValue > (float)m_Max)
		{
			m_PreviousValue = (float)m_Max;
			m_Add = false;
		}
		else if (m_PreviousValue < (float)m_Min)
		{
			m_PreviousValue = (float)m_Min;
			m_Add = true;
		}

		return m_PreviousValue;
	}
};
#pragma once

#include "../Header Files/Sensor.h"

/// <summary>
/// Humidity sensor class
/// Inherits from Sensor class
/// </summary>
class HumiditySensor : public Sensor<float, float>
{
private:
	bool m_Add = true;
	uint32_t m_Min, m_Max;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="HumiditySensor"/> class.
	/// Names the sensor "Humidity".
	/// </summary>
	/// <param name="min"> The minimum simulated value. </param>
	/// <param name="max"> The maximum simulated value. </param>
	HumiditySensor(uint32_t min = 0, uint32_t max = 100) 
		: Sensor("Humidity"), m_Min(min), m_Max(max)
	{
		std::srand(std::time(nullptr));
	}

	/// <summary>
	/// Reads the sensor value.
	/// Simulates the sensor value by adding or subtracting a random number between 0 and 1 to the previous value.
	/// </summary>
	/// <returns> The simulated sensor value. </returns>
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

	/// <summary>
	/// Gets the sensor value for today.
	/// </summary>
	/// <returns> The simulated sensor value. </returns>
	float GetToday()
	{
		return Read();
	}

	/// <summary>
	/// Gets the sensor value for yesterday.
	/// Simulates by adding or subtacting a random number between 0 and 10 to the previous value.
	/// </summary>
	/// <returns> The simulated sensor value. </returns>
	float GetYesterday()
	{
		if ((float)rand() / (float)RAND_MAX > 0.9)
		{
			return m_PreviousValue + (float)rand() / (float)RAND_MAX * 10;
		}
		else
		{
			return m_PreviousValue - (float)rand() / (float)RAND_MAX * 10;
		}
	}
};
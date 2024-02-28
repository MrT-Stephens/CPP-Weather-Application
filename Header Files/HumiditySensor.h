#pragma once

#include "../Header Files/Sensor.h"

class HumiditySensor : public Sensor<float, float>
{
private:
	bool m_Add = true;
	uint32_t m_Min, m_Max;
public:
	HumiditySensor(uint32_t min = 0, uint32_t max = 100) 
		: Sensor("Humidity"), m_Min(min), m_Max(max)
	{
		std::srand(std::time(nullptr));
	}

	float Read() override
	{
		float random = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
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

	float GetToday()
	{
		return Read();
	}

	float GetYesterday()
	{
		uint32_t random = std::rand() % m_Max;

		if (m_PreviousValue - (float)random < (float)m_Min)
		{
			return m_Min;
		}
		else if (m_PreviousValue - (float)random > (float)m_Max)
		{
			return m_Max;
		}
		else
		{
			return m_PreviousValue - (float)random;
		}
	}
};
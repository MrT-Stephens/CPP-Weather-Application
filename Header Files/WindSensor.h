#pragma once

#include "../Header Files/Sensor.h"

class WindSensor : public Sensor<float, float>
{
private:
	bool m_Add = true;
	int32_t m_Min, m_Max;
public:
	WindSensor(uint32_t min = 0, uint32_t max = 50)
		: Sensor("Wind"), m_Min(min), m_Max(max)
	{
		std::srand(std::time(nullptr));
	}

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

	std::string GetWindDirection()
	{
		switch (rand() % 8)
		{
		case 0: return "North";
		case 1: return "North-East";
		case 2: return "East";
		case 3: return "South-East";
		case 4: return "South";
		case 5: return "South-West";
		case 6: return "West";
		case 7: return "North-West";
		default: return "North";
		}
	}
};
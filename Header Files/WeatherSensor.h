#pragma once

#include "../Header Files/Sensor.h"

#include <math.h>

enum class WeatherType : uint8_t
{
	Sunny,
	Cloudy,
	SunnyCloudy,
	Rainy,
	Snowy,
	Thunderstorm
};

class WeatherSensor : public Sensor<std::string, uint32_t>
{
public:
	WeatherSensor() : Sensor("Weather") 
	{ 
		std::srand(std::time(nullptr));
	}

	std::string Read() override
	{
		std::string img_path;

		m_PreviousValue = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) > 0.75) ? m_PreviousValue + 1 : m_PreviousValue + 0;

		switch ((WeatherType)m_PreviousValue)
		{
		case WeatherType::Sunny:
			img_path = "sun.png";
			break;
		case WeatherType::Cloudy:
			img_path = "cloud.png";
			break;
		case WeatherType::SunnyCloudy:
			img_path = "cloud-sun.png";
			break;
		case WeatherType::Rainy:
			img_path = "rain.png";
			break;
		case WeatherType::Snowy:
			img_path = "snow.png";
			break;
		case WeatherType::Thunderstorm:
			img_path = "thunder.png";
			break;
		default:
			img_path = "sun.png";
			m_PreviousValue = 0;
			break;
		}

		return img_path;
	}
};
#pragma once

#include "../Header Files/Sensor.h"

#include <math.h>

/// <summary>
/// Enum class for the different types of weather
/// </summary>
enum class WeatherType : uint8_t
{
	Sunny,
	Cloudy,
	SunnyCloudy,
	Rainy,
	Snowy,
	Thunderstorm
};

/// <summary>
/// Weather sensor class that inherits from the sensor class
/// This class is used to simulate the weather sensor
/// </summary>
class WeatherSensor : public Sensor<std::string, uint32_t>
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="WeatherSensor"/> class.
	/// Names the sensor "Weather".
	/// </summary>
	WeatherSensor() : Sensor("Weather") 
	{ 
		std::srand(std::time(nullptr));
	}

	/// <summary>
	/// Reads the sensor and returns a string representing the weather.
	/// The string is the path to the image of the weather.
	/// </summary>
	/// <returns> String representing the weather images path. </returns>
	std::string Read() override
	{
		std::string img_path;

		m_PreviousValue = ((float)rand() / (float)RAND_MAX > 0.90f) ? m_PreviousValue + 1 : m_PreviousValue + 0;

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
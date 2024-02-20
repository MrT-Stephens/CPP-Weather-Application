#pragma once

#include "../Header Files/Sensor.h"

enum class WeatherType : uint8_t
{
	Sunny,
	Cloudy,
	SunnyCloudy,
	Rainy,
	Snowy,
	Thunderstorm,
	Count
};

class WeatherSensor : public Sensor<WeatherType>
{
public:
	WeatherSensor() : Sensor("Weather") 
	{ 
		std::srand(std::time(nullptr));
	}

	WeatherType Read() override
	{
		return static_cast<WeatherType>(rand() % static_cast<uint8_t>(WeatherType::Count));
	}
};
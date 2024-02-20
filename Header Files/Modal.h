#pragma once

#include "../Header Files/WeatherSensor.h"

#include <memory>
#include <chrono>

class Modal
{
private:
	std::chrono::seconds m_SampleRate;
	std::unique_ptr<WeatherSensor> m_WeatherSensor;
public:
	Modal(uint64_t sample_rate_s);

	WeatherSensor* GetWeatherSensor() const { return m_WeatherSensor.get(); }

	std::chrono::seconds GetSampleRate() const { return m_SampleRate; }
};
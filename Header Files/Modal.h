#pragma once

#include "../Header Files/WeatherSensor.h"
#include "../Header Files/TimeSensor.h"
#include "../Header Files/HumiditySensor.h"
#include "../Header Files/NoCopy.h"

#include <memory>
#include <chrono>

class Modal : private NoCopy
{
private:
	std::chrono::seconds m_SampleRate;
	std::shared_ptr<WeatherSensor> m_WeatherSensor;
	std::shared_ptr<TimeSensor> m_TimeSensor;
	std::shared_ptr<HumiditySensor> m_HumiditySensor;
public:
	Modal(uint64_t sample_rate_s) 
		: m_SampleRate(sample_rate_s) 
	{ 
		m_WeatherSensor = std::make_shared<WeatherSensor>();
		m_TimeSensor = std::make_shared<TimeSensor>();
		m_HumiditySensor = std::make_shared<HumiditySensor>(20, 80);
	}

	std::shared_ptr<WeatherSensor> GetWeatherSensor() const { return m_WeatherSensor; }
	std::shared_ptr<TimeSensor> GetTimeSensor() const { return m_TimeSensor; }
	std::shared_ptr<HumiditySensor> GetHumiditySensor() const { return m_HumiditySensor; }

	std::chrono::seconds GetSampleRate() const { return m_SampleRate; }
};
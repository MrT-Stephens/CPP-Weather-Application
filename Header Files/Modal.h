#pragma once

#include "../Header Files/WeatherSensor.h"
#include "../Header Files/TimeSensor.h"
#include "../Header Files/HumiditySensor.h"
#include "../Header Files/TempratureSensor.h"
#include "../Header Files/WindSensor.h"
#include "../Header Files/NoCopy.h"

#include <memory>
#include <chrono>
#include <math.h>

class Modal : private NoCopy
{
private:
	std::chrono::seconds m_SampleRate;
	std::shared_ptr<WeatherSensor> m_WeatherSensor;
	std::shared_ptr<TimeSensor> m_TimeSensor;
	std::shared_ptr<HumiditySensor> m_HumiditySensor;
	std::shared_ptr<TempratureSensor> m_TempratureSensor;
	std::shared_ptr<WindSensor> m_WindSensor;
public:
	Modal(uint64_t sample_rate_s) 
		: m_SampleRate(sample_rate_s) 
	{ 
		m_WeatherSensor = std::make_shared<WeatherSensor>();
		m_TimeSensor = std::make_shared<TimeSensor>();
		m_HumiditySensor = std::make_shared<HumiditySensor>(20, 80);
		m_TempratureSensor = std::make_shared<TempratureSensor>(-10, 40);
		m_WindSensor = std::make_shared<WindSensor>(5, 40);
	}

	std::shared_ptr<WeatherSensor> GetWeatherSensor() const { return m_WeatherSensor; }
	std::shared_ptr<TimeSensor> GetTimeSensor() const { return m_TimeSensor; }
	std::shared_ptr<HumiditySensor> GetHumiditySensor() const { return m_HumiditySensor; }
	std::shared_ptr<TempratureSensor> GetTempratureSensor() const { return m_TempratureSensor; }
	std::shared_ptr<WindSensor> GetWindSensor() const { return m_WindSensor; }

	float GetDewPoint() const
	{
		return (m_TempratureSensor->GetPreviousValue() - ((100 - m_HumiditySensor->GetPreviousValue()) / 5));
	}

	float GetFeelsLike() const
	{
		return 13.12 + 0.6215 * m_TempratureSensor->GetPreviousValue() - 11.37 * pow(m_WindSensor->GetPreviousValue(), 0.16) + 0.3965 * m_TempratureSensor->GetPreviousValue() * pow(m_WindSensor->GetPreviousValue(), 0.16);
	}

	std::chrono::seconds GetSampleRate() const { return m_SampleRate; }
};
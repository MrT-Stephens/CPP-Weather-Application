#pragma once

#include "../Header Files/WeatherSensor.h"
#include "../Header Files/TimeSensor.h"
#include "../Header Files/HumiditySensor.h"
#include "../Header Files/TempratureSensor.h"
#include "../Header Files/WindSensor.h"
#include "../Header Files/Actuator.h"
#include "../Header Files/NoCopy.h"

#include <memory>
#include <chrono>
#include <math.h>

/// <summary>
/// Modal class is the main class that holds all the sensors and actuators
/// It also contains the logic to calculate the dew point and feels like temperature
/// It also contains the sample rate of the sensors, this is the time interval after which the sensors will be updated.
/// </summary>
class Modal : private NoCopy
{
private:
	std::chrono::seconds m_SampleRate;
	std::shared_ptr<WeatherSensor> m_WeatherSensor;
	std::shared_ptr<TimeSensor> m_TimeSensor;
	std::shared_ptr<HumiditySensor> m_HumiditySensor;
	std::shared_ptr<TempratureSensor> m_TempratureSensor;
	std::shared_ptr<WindSensor> m_WindSensor;
	std::shared_ptr<Actuator<float>> m_WindTurbine, m_Heater, m_Cooler;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Modal"/> class.
	/// Initalizes all the sensors and actuators.
	/// </summary>
	/// <param name="sample_rate_s"> The sample rate in seconds. </param>
	Modal(uint64_t sample_rate_s) 
		: m_SampleRate(sample_rate_s) 
	{ 
		// Sensors Initialization
		m_WeatherSensor = std::make_shared<WeatherSensor>();
		m_TimeSensor = std::make_shared<TimeSensor>();
		m_HumiditySensor = std::make_shared<HumiditySensor>(20, 80);
		m_TempratureSensor = std::make_shared<TempratureSensor>(-10, 40);
		m_WindSensor = std::make_shared<WindSensor>(5, 40);

		// Actuators Initialization
		m_WindTurbine = std::make_shared<Actuator<float>>("Wind Turbine", ActuatorTriggerType::GreaterThan, 50.0f);
		m_Heater = std::make_shared<Actuator<float>>("Heater", ActuatorTriggerType::LessThan, 0.0f);
		m_Cooler = std::make_shared<Actuator<float>>("Cooler", ActuatorTriggerType::GreaterThan, 30.0f);
	}

	/// <summary>
	/// Gettters for the sensors and actuators
	/// </summary>
	/// <returns> A shared pointer to the sensor or actuator. </returns>
	std::shared_ptr<WeatherSensor> GetWeatherSensor() const { return m_WeatherSensor; }
	std::shared_ptr<TimeSensor> GetTimeSensor() const { return m_TimeSensor; }
	std::shared_ptr<HumiditySensor> GetHumiditySensor() const { return m_HumiditySensor; }
	std::shared_ptr<TempratureSensor> GetTempratureSensor() const { return m_TempratureSensor; }
	std::shared_ptr<WindSensor> GetWindSensor() const { return m_WindSensor; }

	std::shared_ptr<Actuator<float>> GetWindTurbine() const { return m_WindTurbine; }
	std::shared_ptr<Actuator<float>> GetHeater() const { return m_Heater; }
	std::shared_ptr<Actuator<float>> GetCooler() const { return m_Cooler; }

	/// <summary>
	/// Gets the dew point.
	/// The dew point is the temperature to which air must be cooled to become saturated with water vapor.
	/// </summary>
	/// <returns> The dew point. </returns>
	float GetDewPoint() const
	{
		return (m_TempratureSensor->GetPreviousValue() - ((100 - m_HumiditySensor->GetPreviousValue()) / 5));
	}

	/// <summary>
	/// Gets the feels like temperature.
	/// The feels like temperature is the temperature that the human body feels when the air temperature is combined with the wind speed.
	/// </summary>
	/// <returns> The feels like temperature. </returns>
	float GetFeelsLike() const
	{
		return 13.12 + 0.6215 * m_TempratureSensor->GetPreviousValue() - 11.37 * pow(m_WindSensor->GetPreviousValue(), 0.16) + 0.3965 * m_TempratureSensor->GetPreviousValue() * pow(m_WindSensor->GetPreviousValue(), 0.16);
	}

	std::chrono::seconds GetSampleRate() const { return m_SampleRate; }
};
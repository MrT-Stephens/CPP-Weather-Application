#pragma once

#include "../Header Files/Sensor.h"

/// <summary>
/// A sensor that reads the current time and date.
/// Inherited from the Sensor class.
/// </summary>
class TimeSensor : public Sensor<std::tm, std::tm>
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TimeSensor"/> class.
	/// Names the sensor "Time".
	/// </summary>
	TimeSensor() : Sensor("Time")
	{
		m_PreviousValue = Read();
	}

	/// <summary>
	/// Reads the current time and date.
	/// </summary>
	/// <returns> The current time and date. </returns>
	std::tm Read() override
	{
		time_t now = std::time(0);
		m_PreviousValue = *std::localtime(&now);
		return m_PreviousValue;
	}

	/// <summary>
	/// A static function that formats a time and date according to a format code.
	/// </summary>
	/// <param name="time"> The time and date to format. </param>
	/// <param name="format_code"> The format code. </param>
	/// <returns> The formatted time and date. </returns>
	static std::string FormatTime(const std::tm& time, const std::string& format_code)
	{
		char buffer[100];

		strftime(buffer, 80, format_code.c_str(), &time);

		return std::string(buffer);
	}
};
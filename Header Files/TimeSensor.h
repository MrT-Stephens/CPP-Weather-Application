#pragma once

#include "../Header Files/Sensor.h"

class TimeSensor : public Sensor<std::tm, std::tm>
{
public:
	TimeSensor() : Sensor("Time")
	{
		m_PreviousValue = Read();
	}

	std::tm Read() override
	{
		time_t now = std::time(0);
		m_PreviousValue = *std::localtime(&now);
		return m_PreviousValue;
	}

	static std::string FormatTime(const std::tm& time, const std::string& format_code)
	{
		char buffer[100];

		strftime(buffer, 80, format_code.c_str(), &time);

		return std::string(buffer);
	}
};
#pragma once

#include <string>
#include <ctype.h>
#include <ctime>

template <typename Type>
class Sensor
{
protected:
	std::string m_Name;
	Type m_PreviousValue;
public:
	Sensor(const std::string& name) : m_Name(name), m_PreviousValue(Type()) { }

	virtual Type Read() = 0;

	std::string GetName() const { return m_Name; }
};
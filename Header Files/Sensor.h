#pragma once

#include "../Header Files/NoCopy.h"

#include <string>
#include <ctype.h>
#include <ctime>

template <typename ReadType, typename PrevType>
class Sensor : private NoCopy
{
protected:
	std::string m_Name;
	PrevType m_PreviousValue;
public:
	Sensor(const std::string& name) : m_Name(name), m_PreviousValue(PrevType()) { }

	virtual ReadType Read() = 0;

	std::string GetName() const { return m_Name; }
};
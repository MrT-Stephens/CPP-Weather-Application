#pragma once

#include "../Header Files/NoCopy.h"

#include <string>
#include <ctype.h>
#include <ctime>

/// <summary>
/// A sensor class that reads a value and stores the previous value.
/// Used to simulate a sensor that reads a value and stores the previous value.
/// </summary>
/// <typeparam name="ReadType"> The type of the value that the sensor reads. </typeparam>
/// <typeparam name="PrevType"> The type of the previous value that the sensor stores. </typeparam>
template <typename ReadType, typename PrevType>
class Sensor : private NoCopy
{
protected:
	std::string m_Name;
	PrevType m_PreviousValue;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Sensor{ReadType, PrevType}"/> class.
	/// </summary>
	/// <param name="name"> The name of the sensor. </param>
	Sensor(const std::string& name) : m_Name(name), m_PreviousValue(PrevType()) { }

	virtual ReadType Read() = 0;

	std::string GetName() const { return m_Name; }

	ReadType GetPreviousValue() const { return m_PreviousValue; }
};
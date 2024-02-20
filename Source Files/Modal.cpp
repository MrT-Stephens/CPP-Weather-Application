#include "../Header Files/Modal.h"

Modal::Modal(uint64_t sample_rate_s)
	: m_SampleRate(sample_rate_s)
{
	m_WeatherSensor = std::make_unique<WeatherSensor>();
}
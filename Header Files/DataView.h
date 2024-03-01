#pragma once

#include <array>

#include "../Header Files/View.h"

class DataView : public View
{
private:
	// Header Items
	cycfi::elements::label m_HeaderUser{ "Hello, User!" };

	// Time and Date Items
	cycfi::elements::label m_TimeLabel{ "21:00" };
	cycfi::elements::label m_DateLabel{ "Monday 19 - February 2024" };

	// Weather Items
	cycfi::elements::image m_WeatherImage{ "sun.png", 0.4f };
	std::array<std::pair<cycfi::elements::label, cycfi::elements::image>, 5> m_WeatherTimeLabels
	{
		std::make_pair(cycfi::elements::label{ "19:00" }, cycfi::elements::image{ "sun.png", 0.05f }),
		std::make_pair(cycfi::elements::label{ "20:00" }, cycfi::elements::image{ "sun.png", 0.05f }),
		std::make_pair(cycfi::elements::label{ "21:00" }, cycfi::elements::image{ "sun.png", 0.05f }),
		std::make_pair(cycfi::elements::label{ "22:00" }, cycfi::elements::image{ "sun.png", 0.05f }),
		std::make_pair(cycfi::elements::label{ "23:00" }, cycfi::elements::image{ "sun.png", 0.05f })
	};
	
	// Humidity Items
	cycfi::elements::label m_HumidityLabel{ "70.00%" };
	cycfi::elements::label m_HumidityYesterdayLabel{ "Up 18% from yesterday" };

	// Wind Items
	cycfi::elements::label m_WindLabel{ "70" };
	cycfi::elements::label m_WindDirectionLabel{ "North" };

	// Temperature Items
	cycfi::elements::label m_TemperatureLabel{ "25" };
	cycfi::elements::label m_TemperatureDewPointLabel{ "28" };
	cycfi::elements::label m_TemperatureFeelsLikeLabel{ "28" };
	cycfi::elements::label m_TemperatureYesterdayLabel{ "26" };

public:
	DataView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit);

	cycfi::elements::element_ptr InitView() override;

	void UpdateTimeAndDate(const std::string& time_hh24_mm_ss, const std::string& date_day_dd_mon_yyyy);

	void UpdateWeather(const std::string& weather, uint32_t current_hour);

	void UpdateHumidity(float humidity, float humidity_yesterday);

	void UpdateWind(float wind_speed, const std::string& wind_direction);

	void UpdateTemperature(float temperature, float dew_point, float feels_like, float temperature_yesterday);
};
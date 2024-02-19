#pragma once

#include <array>

#include "../Header Files/View.h"

class MainView : public View
{
private:
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
	cycfi::elements::label m_HumidityLabel{ "70%" };
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
	MainView(std::shared_ptr<cycfi::elements::window> window);

	void InitView() override;

	void UpdateView() override;

	void UpdateTimeAndDate(const std::string& time_hh24_mm, const std::string_view& date_day_dd_mon_yyyy);

	void UpdateWeather(const std::array<std::pair<std::string_view, std::string_view>, 5>& weather_and_times);

	void UpdateHumidity(const uint32_t& humidity, const uint32_t& humidity_yesterday);

	void UpdateWind(const uint32_t& wind_speed, const std::string_view& wind_direction);

	void UpdateTemperature(const uint32_t& temperature, const uint32_t& dew_point, const uint32_t& feels_like, const uint32_t& temperature_yesterday);
};
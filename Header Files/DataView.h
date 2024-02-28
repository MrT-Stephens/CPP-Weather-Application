#pragma once

#include <array>

#include "../Header Files/View.h"

class DataView : public View
{
public:
	using MenuItem = cycfi::elements::proxy<cycfi::elements::margin_element<cycfi::elements::hmargin_rect, 
					 cycfi::elements::halign_element<cycfi::elements::label>>, cycfi::elements::basic_menu_item_element>;
private:
	// Menu Items
	MenuItem m_AboutMenuItem{ cycfi::elements::menu_item("About") };
	MenuItem m_ActuatorsMenuItem{ cycfi::elements::menu_item("Actuators") };
	MenuItem m_UsersMenuItem{ cycfi::elements::menu_item("Users") };
	MenuItem m_SignOutMenuItem{ cycfi::elements::menu_item("Sign Out") };

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

	void InitView() override;

	void UpdateView() override;

	void UpdateTimeAndDate(const std::string& time_hh24_mm, const std::string& date_day_dd_mon_yyyy);

	void UpdateWeather(const std::string& weather, uint32_t current_hour);

	void UpdateHumidity(float humidity, float humidity_yesterday);

	void UpdateWind(int32_t wind_speed, const std::string& wind_direction);

	void UpdateTemperature(int32_t temperature, int32_t dew_point, int32_t feels_like, int32_t temperature_yesterday);

	void SetOnAboutMenuItemClicked(std::function<void()> callback);

	void SetOnActuatorsMenuItemClicked(std::function<void()> callback);

	void SetOnUsersMenuItemClicked(std::function<void()> callback);
	
	void SetOnSignOutMenuItemClicked(std::function<void()> callback);
};
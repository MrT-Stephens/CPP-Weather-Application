#include "../Header Files/MainView.h"

MainView::MainView(std::shared_ptr<cycfi::elements::window> window)
    : View(window)
{

}

void MainView::InitView()
{
    auto box = cycfi::elements::margin({ 10, 10, 10, 10 }, cycfi::elements::rbox_element{ cycfi::elements::rbox(m_BackgroundColor.level(1.5f)) });

    auto menu_button = cycfi::elements::button_menu("Menu", cycfi::elements::menu_position::bottom_left);

    auto menu = cycfi::elements::layer(
        cycfi::elements::vtile(
            cycfi::elements::menu_item("Account"),
            cycfi::elements::menu_item("Settings"),
            cycfi::elements::menu_item("About"),
            cycfi::elements::menu_item("Admin"),
            cycfi::elements::menu_item("Sign Out")
        ), cycfi::elements::panel{}
    );

    menu_button.menu(menu);

    content(
        cycfi::elements::pane(
            cycfi::elements::htile(
                cycfi::elements::align_middle(
                    cycfi::elements::static_text_box("Hello, User!", cycfi::elements::get_theme().text_box_font.size(20.0f))
                ),
                cycfi::elements::align_right(
                    menu_button
                )
            ),
            cycfi::elements::htile(
                cycfi::elements::vtile(
                    cycfi::elements::vstretch(1.0f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Time",
                                cycfi::elements::layer(
                                    cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center_middle(
                                                m_TimeLabel.font_size(60.0f)
                                            ),
                                            cycfi::elements::align_center_middle(
                                                m_DateLabel.font_size(20.0f)
                                            )
                                        )
                                    ),
                                    box
                                ), 1.3f, true
                            )
                        )
                    ),
                    cycfi::elements::vstretch(1.5f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Weather",
                                cycfi::elements::layer(
									cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::margin({ 20, 20, 20, 20},
												    m_WeatherImage
                                                )
											),
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::htile(
                                                    cycfi::elements::margin({10, 10, 10, 10},
                                                        cycfi::elements::vtile(
                                                            m_WeatherTimeLabels[0].first.font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                m_WeatherTimeLabels[0].second
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            m_WeatherTimeLabels[1].first.font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                m_WeatherTimeLabels[1].second
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::layer(
                                                        cycfi::elements::margin({ 10, 10, 10, 10 },
                                                            cycfi::elements::vtile(
                                                                m_WeatherTimeLabels[2].first.font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                                cycfi::elements::vspace(5.0f),
                                                                cycfi::elements::align_center(
                                                                    m_WeatherTimeLabels[2].second
                                                                )
                                                            )
                                                        ),
                                                        cycfi::elements::rbox(m_BackgroundColor)
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            m_WeatherTimeLabels[3].first.font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                m_WeatherTimeLabels[3].second
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            m_WeatherTimeLabels[4].first.font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                m_WeatherTimeLabels[4].second
                                                            )
                                                        )
                                                    )
                                                )
                                            )
										)
                                    ),
									box
								), 1.3f, true
                            )
                        )
                    )
                ),
                cycfi::elements::vtile(
                    cycfi::elements::vstretch(1.0f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Humidity",
                                cycfi::elements::layer(
								    cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center(
                                                m_HumidityLabel.font_size(60.0f)
                                            ),
                                            cycfi::elements::align_center_middle(
                                                m_HumidityYesterdayLabel.font_size(20.0f)
                                            )
									    )								
                                    ),
								    box
							    ), 1.3f, true
                            )
                        )
                    ),
                    cycfi::elements::vstretch(1.0f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Wind",
                                cycfi::elements::layer(
                                    cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center(
                                                cycfi::elements::htile(
                                                    m_WindLabel.font_size(60.0f),
                                                    cycfi::elements::hspace(5.0f),
                                                    cycfi::elements::label("MPH").font_size(20.0f)
                                                )
                                            ),
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::htile(
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        m_WindDirectionLabel.font_size(20.0f)
                                                    )
                                                )
                                            )
                                        )
                                    ),
                                    box
                                ), 1.3f, true
                            )
                        )
                    ),
                    cycfi::elements::vstretch(1.5f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Temperature",
                                cycfi::elements::layer(
								    cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::htile(
                                                    m_TemperatureLabel.font_size(70.0f),
                                                    cycfi::elements::hspace(5.0f),
                                                    cycfi::elements::label("\u00B0C").font_size(70.0f)
                                                )
                                            ),
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::htile(
                                                    cycfi::elements::margin({10, 10, 10, 10},
                                                        cycfi::elements::vtile(
                                                            cycfi::elements::label("Dew Point").font_size(15.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::htile(
                                                                m_TemperatureDewPointLabel.font_size(20.0f),
                                                                cycfi::elements::hspace(5.0f),
                                                                cycfi::elements::label("\u00B0C").font_size(20.0f)
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            cycfi::elements::label("Yesterday").font_size(15.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::htile(
                                                                m_TemperatureYesterdayLabel.font_size(20.0f),
                                                                cycfi::elements::hspace(5.0f),
                                                                cycfi::elements::label("\u00B0C").font_size(20.0f)
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            cycfi::elements::label("Feels like").font_size(15.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::htile(
                                                                m_TemperatureFeelsLikeLabel.font_size(20.0f),
                                                                cycfi::elements::hspace(5.0f),
                                                                cycfi::elements::label("\u00B0C").font_size(20.0f)
                                                            )
                                                        )
                                                    )
                                                )
                                            )
									    )								
                                    ),
								    box
							    ), 1.3f, true
                            )
                        )
                    )
                )
            )
        ),
        cycfi::elements::box(m_BackgroundColor)
    );
}

void MainView::UpdateView()
{
    this->InitView();
}

void MainView::UpdateTimeAndDate(const std::string& time_hh24_mm, const std::string_view& date_day_dd_mon_yyyy)
{
	m_TimeLabel.set_text(time_hh24_mm);
	m_DateLabel.set_text(date_day_dd_mon_yyyy);
}

void MainView::UpdateWeather(const std::array<std::pair<std::string_view, std::string_view>, 5>& weather_and_times)
{
    for (uint64_t i = 0; i < weather_and_times.size(); ++i)
    {
        m_WeatherTimeLabels[i].first.set_text(weather_and_times[i].first);
		m_WeatherTimeLabels[i].second.set_image(weather_and_times[i].second);
    }
}

void MainView::UpdateHumidity(const uint32_t& humidity, const uint32_t& humidity_yesterday)
{
    m_HumidityLabel.set_text(std::to_string(humidity) + "%");
	m_HumidityYesterdayLabel.set_text("Up " + std::to_string(humidity - humidity_yesterday) + "% from yesterday");
}

void MainView::UpdateWind(const uint32_t& wind_speed, const std::string_view& wind_direction)
{
	m_WindLabel.set_text(std::to_string(wind_speed));
	m_WindDirectionLabel.set_text(wind_direction);
}

void MainView::UpdateTemperature(const uint32_t& temperature, const uint32_t& dew_point, const uint32_t& feels_like, const uint32_t& temperature_yesterday)
{
	m_TemperatureLabel.set_text(std::to_string(temperature));
	m_TemperatureDewPointLabel.set_text(std::to_string(dew_point));
	m_TemperatureFeelsLikeLabel.set_text(std::to_string(feels_like));
	m_TemperatureYesterdayLabel.set_text(std::to_string(temperature_yesterday));
}
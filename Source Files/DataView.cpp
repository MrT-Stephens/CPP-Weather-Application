#include "../Header Files/DataView.h"

DataView::DataView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit)
    : View(main_view, user_access, request_exit)
{

}

cycfi::elements::element_ptr DataView::InitView()
{
    auto box = cycfi::elements::margin({ 10, 10, 10, 10 }, cycfi::elements::rbox_element{ cycfi::elements::rbox(m_BackgroundColor.level(1.5f)) });

    return cycfi::elements::share(
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
    );
}

void DataView::UpdateTimeAndDate(const std::string& time_hh24_mm_ss, const std::string& date_day_dd_mon_yyyy)
{
	m_TimeLabel.set_text(time_hh24_mm_ss);
	m_DateLabel.set_text(date_day_dd_mon_yyyy);
}

void DataView::UpdateWeather(const std::string& weather, uint32_t current_hour)
{
    m_WeatherImage.set_image(weather);

    for (uint64_t i = 0; i < m_WeatherTimeLabels.size(); i++)
    {
        // Calculate the adjusted hour based on the index
        uint32_t adjusted_hour = current_hour + i - 2; // Adjusted hour = current_hour + index - 2

        if (adjusted_hour < 0)
        {
			adjusted_hour = 24 + adjusted_hour;
		}
        else if (adjusted_hour > 23)
        {
			adjusted_hour = adjusted_hour - 24;
		}

        std::string formatted_hour = std::to_string(adjusted_hour);
        formatted_hour = std::string(2 - formatted_hour.length(), '0') + formatted_hour + ":00";

        // Set the adjusted hour to the text of the first element in the pair
        m_WeatherTimeLabels[i].first.set_text(formatted_hour);

        // Set the weather image for the second element in the pair
        m_WeatherTimeLabels[i].second.set_image(weather);
    }
}

void DataView::UpdateHumidity(float humidity, float humidity_yesterday)
{
    std::ostringstream ss;

    ss << std::fixed << std::setprecision(2) << humidity << "%";
    m_HumidityLabel.set_text(ss.str());

    ss.str("");
    ss << std::fixed << std::setprecision(2) << "Up " << humidity - humidity_yesterday << "% from yesterday";
	m_HumidityYesterdayLabel.set_text(ss.str());
}

void DataView::UpdateWind(int32_t wind_speed, const std::string& wind_direction)
{
	m_WindLabel.set_text(std::to_string(wind_speed));
	m_WindDirectionLabel.set_text(wind_direction);
}

void DataView::UpdateTemperature(float temperature, float dew_point, float feels_like, float temperature_yesterday)
{
    std::ostringstream ss;

    ss << std::fixed << std::setprecision(2) << temperature;
	m_TemperatureLabel.set_text(ss.str());

    ss.str("");
    ss << std::fixed << std::setprecision(2) << dew_point;
	m_TemperatureDewPointLabel.set_text(ss.str());

    ss.str("");
	ss << std::fixed << std::setprecision(2) << feels_like;
	m_TemperatureFeelsLikeLabel.set_text(ss.str());

    ss.str("");
    ss << std::fixed << std::setprecision(2) << temperature_yesterday;
	m_TemperatureYesterdayLabel.set_text(ss.str());
}
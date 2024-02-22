#include "../Header Files/Controller.h"

Controller::Controller(int argc, char* argv[], std::string name, std::string id)
	: app(argc, argv, name, id), m_Window(std::make_shared<cycfi::elements::window>(this->name()))
{
	m_Window->on_close = [this]()
	{
		this->stop();
	};

	m_MainView = std::make_shared<cycfi::elements::view>(*m_Window.get());

	m_CurrentView = std::make_shared<LoginView>(m_MainView);

	m_Modal = std::make_unique<Modal>(5);
}

void Controller::Init()
{
	if (auto view = std::any_cast<std::shared_ptr<LoginView>>(m_CurrentView))
	{
		view->SetLoginCallback([this, view](bool)
			{
				if (m_Authenticator.Authenticate(view->GetEmail(), view->GetPassword()).first)
				{
					auto&& on_click = [this]()
					{
						m_MainView->post(std::chrono::seconds(1), [this]()
						{
							m_CurrentView = std::make_shared<DataView>(m_MainView);

							if (auto view = std::any_cast<std::shared_ptr<DataView>>(m_CurrentView))
							{
								view->InitView();
							}
						});
					};

					auto popup = cycfi::elements::message_box1(*m_MainView.get(), "You have successfully logged in", cycfi::elements::icons::info, on_click);

					cycfi::elements::open_popup(popup, *m_MainView.get());
				}
				else
				{
					auto&& on_click = []()
					{
						return;
					};

					auto popup = cycfi::elements::message_box1(*m_MainView.get(), "Invalid login infomation", cycfi::elements::icons::info, on_click);

					cycfi::elements::open_popup(popup, *m_MainView.get());
				}
			}
		);

		view->InitView();
	}

	this->run();
}

void Controller::UpdateSensorData()
{
	if (auto view = std::any_cast<std::shared_ptr<DataView>>(m_CurrentView))
	{
		std::string img_path = "";

		switch (m_Modal->GetWeatherSensor()->Read())
		{
		case WeatherType::Sunny:
			img_path = "sun.png";
			break;
		case WeatherType::Cloudy:
			img_path = "cloud.png";
			break;
		case WeatherType::SunnyCloudy:
			img_path = "cloud-sun.png";
			break;
		case WeatherType::Rainy:
			img_path = "rain.png";
			break;
		case WeatherType::Snowy:
			img_path = "snow.png";
			break;
		case WeatherType::Thunderstorm:
			img_path = "thunder.png";
			break;
		}


		view->UpdateWeather(img_path, 23);
		view->UpdateView();

		m_MainView->post(m_Modal->GetSampleRate(), [this]()
		{
			this->UpdateSensorData();
		});
	}
}
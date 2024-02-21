#include "../Header Files/Controller.h"

Controller::Controller(int argc, char* argv[], std::string name, std::string id)
	: app(argc, argv, name, id), m_Window(std::make_shared<cycfi::elements::window>(this->name()))
{
	m_Window->on_close = [this]()
	{
		this->stop();
	};

	m_MainView = std::make_shared<cycfi::elements::view>(*m_Window.get());

	m_CurrentView = std::make_shared<DataView>(m_MainView);

	m_Modal = std::make_unique<Modal>(5);
}

void Controller::Init()
{
	if (auto view = std::any_cast<std::shared_ptr<DataView>>(m_CurrentView))
	{
		view->InitView();
	}

	m_MainView->post(m_Modal->GetSampleRate(), [this]()
	{
		this->UpdateSensorData();
	});

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
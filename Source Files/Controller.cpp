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
}

void Controller::Init()
{
	if (auto view = std::any_cast<std::shared_ptr<DataView>>(m_CurrentView))
	{
		view->InitView();

		m_MainView->post(std::chrono::seconds{2}, [this]()
		{
			if (auto view = std::any_cast<std::shared_ptr<DataView>>(m_CurrentView))
			{
				view->UpdateWeather("cloud.png", 23);
				view->UpdateView();
			}
		});

		m_MainView->post(std::chrono::seconds{ 4 }, [this]()
		{
			m_CurrentView = std::make_shared<LoginView>(m_MainView);

			if (auto view = std::any_cast<std::shared_ptr<LoginView>>(m_CurrentView))
			{
				view->UpdateView();
			}
		});
	}

	this->run();
}
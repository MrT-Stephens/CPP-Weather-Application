#include "../Header Files/Controller.h"

Controller::Controller(int argc, char* argv[], std::string name, std::string id)
	: app(argc, argv, name, id), m_Window(std::make_shared<cycfi::elements::window>(this->name()))
{
	m_Window->on_close = [this]()
		{
			this->stop();
		};

	m_CurrentView = std::make_shared<MainView>(m_Window);
}

void Controller::Init()
{
	if (auto view = std::any_cast<std::shared_ptr<MainView>>(m_CurrentView))
	{
		view->InitView();
		view->UpdateWeather("cloud-sun.png", 23);
		view->InitView();
	}

	this->run();
}
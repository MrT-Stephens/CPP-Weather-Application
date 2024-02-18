#include "../Header Files/Controller.h"

Controller::Controller(std::unique_ptr<cycfi::elements::app> app)
	: m_App(std::move(app)), m_Window(std::make_shared<cycfi::elements::window>(m_App->name()))
{
	m_Window->on_close = [this]()
		{
			m_App->stop();
		};

	m_CurrentView = std::make_unique<LoginView>(m_Window);
}

void Controller::Init()
{
	m_CurrentView->InitView();
	m_App->run();
}
#include "../Header Files/Controller.h"

Controller::Controller(std::unique_ptr<cycfi::elements::app> app)
	: m_App(std::move(app)), m_Window(std::make_shared<cycfi::elements::window>(m_App->name()))
{
	m_Window->on_close = [this]()
		{
			m_App->stop();
		};

	m_CurrentView = std::make_shared<MainView>(m_Window);
}

void Controller::Init()
{
	if (auto view = std::any_cast<std::shared_ptr<MainView>>(m_CurrentView))
	{
		view->InitView();
		view->UpdateTimeAndDate("25:00", "Monday 19 - February 2024");
		view->UpdateView();
	}

	m_App->run();

	if (auto view = std::any_cast<std::shared_ptr<MainView>>(m_CurrentView))
	{
		view->UpdateTimeAndDate("25:00", "Monday 19 - February 2024");
		view->UpdateView();
	}
}
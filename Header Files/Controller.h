#pragma once

#include <elements.hpp>
#include <any>

#include "../Header Files/MainView.h"
#include "../Header Files/LoginView.h"

class Controller
{
protected:
	std::unique_ptr<cycfi::elements::app> m_App;
	std::shared_ptr<cycfi::elements::window> m_Window;
	std::any m_CurrentView;

public:
	Controller(std::unique_ptr<cycfi::elements::app> app);

	void Init();
};
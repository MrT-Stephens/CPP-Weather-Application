#pragma once

#include <elements.hpp>
#include <any>

#include "../Header Files/MainView.h"
#include "../Header Files/LoginView.h"

class Controller : public cycfi::elements::app
{
protected:
	std::shared_ptr<cycfi::elements::window> m_Window;
	std::any m_CurrentView;

public:
	Controller(int argc, char* argv[], std::string name, std::string id);

	void Init();
};
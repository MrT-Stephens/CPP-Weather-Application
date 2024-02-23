#pragma once

#include <elements.hpp>
#include <any>

#include "../Header Files/DataView.h"
#include "../Header Files/LoginView.h"
#include "../Header Files/Modal.h"
#include "../Header Files/Authenticator.h"
#include "../Header Files/NoCopy.h"

class Controller : public cycfi::elements::app, private NoCopy
{
private:
	std::unique_ptr<Modal> m_Modal;
	std::shared_ptr<cycfi::elements::view> m_MainView;
	std::shared_ptr<cycfi::elements::window> m_Window;

	Subject m_CurrentSubject;
	Authenticator m_Authenticator;
	
	std::any m_CurrentView;
public:
	Controller(int argc, char* argv[], std::string name, std::string id);

	void Init();
	void UpdateSensorData();
};
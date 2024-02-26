#pragma once

#include <elements.hpp>
#include <any>

#include "../Header Files/DataView.h"
#include "../Header Files/LoginView.h"
#include "../Header Files/Modal.h"
#include "../Header Files/Authenticator.h"
#include "../Header Files/NoCopy.h"
#include "../Header Files/Resource.h"
#include "../Header Files/UserView.h"

class Controller : public cycfi::elements::app, private NoCopy
{
public:
	using ResourceAccessor = Resource<DataView, UserView>;
private:
	std::unique_ptr<Modal> m_Modal;
	std::shared_ptr<cycfi::elements::view> m_MainView;
	std::shared_ptr<cycfi::elements::window> m_Window;
	ResourceAccessor m_ResourceAccessor;

	Subject m_CurrentSubject;
	Authenticator m_Authenticator;
	
	std::any m_CurrentView;
public:
	Controller(int argc, char* argv[], std::string name, std::string id);

	void Init();
	void UpdateSensorData();
	void InitDataView();
	void InitUserView();
};
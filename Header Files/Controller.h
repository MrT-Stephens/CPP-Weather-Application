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
#include "../Header Files/AboutView.h"

class Controller : public cycfi::elements::app, private NoCopy
{
public:
	using UsersView = UserView<3U>;
	using ResourceAccessor = Resource<AboutView, DataView, UsersView>;
private:
	// Modal Items
	std::unique_ptr<Modal> m_Modal;

	// Window Items
	std::shared_ptr<cycfi::elements::window> m_Window;

	// User auth items
	Subject m_CurrentSubject;
	Authenticator m_Authenticator;
	ResourceAccessor m_ResourceAccessor;
	
	// View Items
	std::shared_ptr<View> m_CurrentView;
	std::shared_ptr<cycfi::elements::view> m_MainView;
	bool m_IsDataView = false;
	cycfi::elements::indirect<cycfi::elements::shared_element<cycfi::elements::element>> m_MainContent{ cycfi::elements::share(cycfi::elements::label("")) };
public:
	Controller(int argc, char* argv[], std::string name, std::string id);

	void Init();
	void InitDataView();
	void InitUserView();
	void InitLoginView();
	void InitAboutView();

	void UpdateDataView();

	void OnClose();
};
#pragma once

#include "../Header Files/Permission.h"
#include "../Header Files/NoCopy.h"

#include <elements.hpp>

class View : private NoCopy
{
protected:
	uint8_t m_UserAccess;
	cycfi::artist::color m_BackgroundColor;
	std::function<void()> m_RequestExit;
	std::shared_ptr<cycfi::elements::view> m_MainView;
public:
	View(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access = (uint8_t)AccessType::NO_ACCESS, std::function<void()> request_exit = []() { return; })
		: m_UserAccess(user_access), m_RequestExit(request_exit), m_MainView(main_view)
	{
		m_BackgroundColor = cycfi::artist::rgba(35, 35, 37, 255);

		// If user access is 'NO ACCESS' then close the application, for safety.
		// This is a safety feature to prevent unauthorized access to the application.
		if (m_UserAccess == (uint8_t)AccessType::NO_ACCESS)
		{
			m_RequestExit();
		}
	}

	virtual cycfi::elements::element_ptr InitView() = 0;
};
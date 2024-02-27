#pragma once

#include "../Header Files/Permission.h"
#include "../Header Files/NoCopy.h"

#include <elements.hpp>

class View : private NoCopy
{
protected:
	uint8_t m_UserAccess;
	cycfi::artist::color m_BackgroundColor;
	std::shared_ptr<cycfi::elements::view> m_MainView;
	std::function<void()> m_RequestExit;
public:
	View(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access = (uint8_t)AccessType::NO_ACCESS, std::function<void()> request_exit = []() { return; })
		: m_MainView(main_view), m_UserAccess(user_access), m_RequestExit(request_exit)
	{
		m_BackgroundColor = cycfi::artist::rgba(35, 35, 37, 255);

		// If user access is 'NO ACCESS' then close the application, for safety.
		// This is a safety feature to prevent unauthorized access to the application.
		if (m_UserAccess == (uint8_t)AccessType::NO_ACCESS)
		{
			m_RequestExit();
		}
	}

	virtual void InitView() = 0;

	virtual void UpdateView() = 0;
};
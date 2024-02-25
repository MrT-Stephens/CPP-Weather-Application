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
public:
	View(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access = (uint8_t)AccessType::NO_ACCESS)
		: m_MainView(main_view), m_UserAccess(user_access)
	{
		m_BackgroundColor = cycfi::artist::rgba(35, 35, 37, 255);

		// If user access is 'NO ACCESS' then close the application, for safety.
		// This is a safety feature to prevent unauthorized access to the application.
		if (m_UserAccess == (uint8_t)AccessType::NO_ACCESS)
		{
			auto&& on_click = []()
			{
				exit(0);
			};

			auto popup = cycfi::elements::message_box1(*m_MainView.get(), "User access is 'NO ACCESS' application will know close for safety.", cycfi::elements::icons::error, on_click);

			cycfi::elements::open_popup(popup, *m_MainView.get());

			m_MainView->post(std::chrono::seconds(5), [this]()
			{
				exit(0);
			});
		}
	}

	virtual void InitView() = 0;

	virtual void UpdateView() = 0;
};
#pragma once

#include "../Header Files/Permission.h"
#include "../Header Files/NoCopy.h"

#include <elements.hpp>

/// <summary>
/// The base class for all views in the application.
/// This class is used to define the basic structure of all views in the application.
/// It is used to define the user access level, the background color, the main view and the request exit function.
/// </summary>
class View : private NoCopy
{
protected:
	uint8_t m_UserAccess;
	cycfi::artist::color m_BackgroundColor;
	std::function<void()> m_RequestExit;
	std::shared_ptr<cycfi::elements::view> m_MainView;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="View"/> class.
	/// Will check if the user has access to the view, if not, the application will close.
	/// </summary>
	/// <param name="main_view"> A shared pointer to the view which is being displayed on screen. </param>
	/// <param name="user_access"> The users access for this view. </param>
	/// <param name="request_exit"> Function which gets called if the user access is 'NO ACCESS'. </param>
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

	// Virtual function which will be used to initialize each view.
	virtual cycfi::elements::element_ptr InitView() = 0;
};
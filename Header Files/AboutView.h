#pragma once

#include "../Header Files/View.h"

class AboutView : public View
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AboutView"/> class.
	/// </summary>
	/// <param name="main_view"> A shared pointer to the view which is being displayed on screen. </param>
	/// <param name="user_access"> The users access for this view. </param>
	/// <param name="request_exit"> Function which gets called if the user access is 'NO ACCESS'. </param>
	AboutView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit)
		: View(main_view, user_access, request_exit)
	{

	}

	/// <summary>
	/// Initializes the about view with the appropriate components.
	/// </summary>
	/// <returns> Returns a shared pointer to all the UI components. </returns>
	cycfi::elements::element_ptr AboutView::InitView()
	{
		return cycfi::elements::share(
			cycfi::elements::hold(
				cycfi::elements::share(
					cycfi::elements::vport(
						cycfi::elements::basic_text_box{
							((AccessType)m_UserAccess == AccessType::READ || (AccessType)m_UserAccess == AccessType::READ_WRITE) ?
							"About\n"
							"This application is an app built in C++ using the elements GUI library. It is an application that simulates a weather app and has various sensors such as time, humidity, wind, temprature, and weather."
							"It also has various actuators that will get triggered based on certain events and these are wind turbine, heater, and cooler."
							"The application also supports user authentication with all of the data being stored within XML files and encrypted for safe-keeping."
							"The application also has a built-in logging system that logs all of the events that occur within the application."
						: "You do not have access to this view."
						}.read_only()
					)
				)
			)
		);
	}
};
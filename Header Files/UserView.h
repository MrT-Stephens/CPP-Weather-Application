#pragma once

#include "../Header Files/View.h"
#include "../Header Files/ElementsTable.h"

class UserView : public View
{
public:
	using Button = cycfi::elements::proxy<cycfi::elements::button_styler_gen<cycfi::elements::button_styler_with_body_color<
				   cycfi::elements::button_styler_with_size<cycfi::elements::basic_button_styler>>>, cycfi::elements::basic_button>;
private:
	// Header Buttons
	Button m_BackButton{ cycfi::elements::button("Back") };
	Button m_AddUserButton{ cycfi::elements::button("Add User") };

	// Table
	std::vector<std::vector<std::string>> m_UserData;

	// Add User Data
	std::string m_Email;
	std::string m_FirstName;
	std::string m_LastName;
	std::string m_Password;
	std::vector<uint8_t> m_AccessLevels;

	std::function<void()> m_AddUserCallback;

	void AddUserPopup();
public:
	UserView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access);

	void InitView() override;

	void UpdateView() override;

	void SetUserData(const std::vector<std::vector<std::string>>& data);

	void SetAddUserCallback(std::function<void()> callback);
};
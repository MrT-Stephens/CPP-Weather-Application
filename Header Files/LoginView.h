#pragma once

#include "../Header Files/View.h"

class LoginView : public View
{
public:
	using Button = cycfi::elements::proxy<cycfi::elements::button_styler_gen<cycfi::elements::button_styler_with_body_color<
				   cycfi::elements::button_styler_with_size<cycfi::elements::basic_button_styler>>>, cycfi::elements::basic_button>;
private:
	Button m_LoginButton{ cycfi::elements::button("Login", 1.1f) };

	std::string m_Email;
	std::string m_Password;
public:
	LoginView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit);
	~LoginView();

	cycfi::elements::element_ptr InitView() override;

	void SetLoginCallback(std::function<void(bool)> callback);

	std::string GetEmail() const { return m_Email; }
	std::string GetPassword() const { return m_Password; }
};
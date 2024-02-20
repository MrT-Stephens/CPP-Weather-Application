#pragma once

#include "../Header Files/View.h"

class LoginView : public View
{
public:
	using u_TextEntry = std::pair<std::_Unrefwrap_helper<cycfi::elements::array_composite<2, cycfi::elements::layer_element>>::type, 
						std::shared_ptr<cycfi::elements::element>>;

	using u_Button = cycfi::elements::proxy<cycfi::elements::button_styler_gen<cycfi::elements::button_styler_with_body_color<
					 cycfi::elements::button_styler_with_size<cycfi::elements::basic_button_styler>>>, cycfi::elements::basic_button>;

private:
	u_TextEntry m_EmailEntry{ cycfi::elements::input_box("", 1.2f) };
	u_TextEntry m_PasswordEntry{ cycfi::elements::input_box("", 1.2f) };
	u_Button m_LoginButton{ cycfi::elements::button("Login", 1.1f) };

public:
	LoginView(std::shared_ptr<cycfi::elements::view> main_view);

	void InitView() override;

	void UpdateView() override;

	void SetLoginCallback(std::function<void(bool)>&& callback);

	std::string_view GetEmail() const;
	std::string_view GetPassword() const;
};
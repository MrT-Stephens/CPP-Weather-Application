#pragma once

#include "../Header Files/View.h"

class UserView : public View
{
public:
	using Button = cycfi::elements::proxy<cycfi::elements::button_styler_gen<cycfi::elements::button_styler_with_body_color<
				   cycfi::elements::button_styler_with_size<cycfi::elements::basic_button_styler>>>, cycfi::elements::basic_button>;
private:
	Button m_BackButton{ cycfi::elements::button("Back") };
	Button m_AddUserButton{ cycfi::elements::button("Add User") };
public:
	UserView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access);

	void InitView() override;

	void UpdateView() override;
};
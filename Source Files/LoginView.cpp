#include "../Header Files/LoginView.h"

LoginView::LoginView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit)
    : View(main_view, user_access, request_exit)
{

}

LoginView::~LoginView()
{
    m_Email = "";
    m_Password = "";
}

cycfi::elements::element_ptr LoginView::InitView()
{
    auto email_entry = cycfi::elements::input_box("", 1.2f);
    auto password_entry = cycfi::elements::input_box("", 1.2f);

    email_entry.second->on_text = [this](std::string_view text)
    {
        m_Email = text.data();
    };

    password_entry.second->on_text = [this](std::string_view text)
	{
		m_Password = text.data();
	};

    return cycfi::elements::share(
        cycfi::elements::margin({ 20, 20, 20, 20 },
            cycfi::elements::vtile(
                cycfi::elements::align_center_middle(
                    cycfi::elements::hmin_size(250,
                        cycfi::elements::align_center(
                            cycfi::elements::pane("Login to your account",
                                cycfi::elements::margin({ 20, 20, 20, 20 },
                                    cycfi::elements::vgrid(
                                        cycfi::elements::vtile(
                                            cycfi::elements::label("Email").text_align(cycfi::elements::canvas::left),
                                            cycfi::elements::hmin_size(200,
                                                cycfi::elements::margin({ 0, 10, 0, 10 },
                                                    email_entry.first
                                                )
                                            )
                                        ),
                                        cycfi::elements::vtile(
                                            cycfi::elements::label("Password").text_align(cycfi::elements::canvas::left),
                                            cycfi::elements::hmin_size(200,
                                                cycfi::elements::margin({ 0, 10, 0, 10 },
                                                    password_entry.first
                                                )
                                            )
                                        ),
                                        cycfi::elements::vtile(
                                            cycfi::elements::margin({ 20, 10, 20, 10 },
                                                m_LoginButton
                                            )
                                        )
                                    )
                                ), 1.3f, true
                            )
                        )
                    )
                )
            )
        )
    );
}

void LoginView::SetLoginCallback(std::function<void(bool)> callback)
{
    m_LoginButton.on_click = callback;
}
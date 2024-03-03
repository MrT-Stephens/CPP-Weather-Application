#include "../Header Files/LoginView.h"

/// <summary>
/// Initializes a new instance of the <see cref="LoginView"/> class.
/// </summary>
/// <param name="main_view"> A shared pointer to the view which is being displayed on screen. </param>
/// <param name="user_access"> The users access for this view. </param>
/// <param name="request_exit"> Function which gets called if the user access is 'NO ACCESS'. </param>
LoginView::LoginView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit)
    : View(main_view, user_access, request_exit)
{

}

/// <summary>
/// For added security, the password and email are set to empty strings.
/// </summary>
LoginView::~LoginView()
{
    m_Email = "";
    m_Password = "";
}

/// <summary>
/// Initializes the login view with the required UI elements.
/// </summary>
/// <returns> A shared pointer to all the UI elements. </returns>
cycfi::elements::element_ptr LoginView::InitView()
{
    // The user can enter their email and password in these input boxes.
    auto email_entry = cycfi::elements::input_box("", 1.2f);
    auto password_entry = cycfi::elements::input_box("", 1.2f);

    // Event handlers for the input boxes, which update the email and password variables.
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

/// <summary>
/// Sets the login button callback.
/// When the user clicks the login button, the callback function is called.
/// </summary>
/// <param name="callback"> The callback function. </param>
void LoginView::SetLoginCallback(std::function<void(bool)> callback)
{
    m_LoginButton.on_click = callback;
}
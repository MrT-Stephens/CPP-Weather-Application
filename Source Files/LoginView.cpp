#include "../Header Files/LoginView.h"

LoginView::LoginView(std::shared_ptr<cycfi::elements::window> window)
    : View(window)
{

}

void LoginView::InitView()
{
    content(
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
                                                    m_EmailEntry.first
                                                )
                                            )
                                        ),
                                        cycfi::elements::vtile(
                                            cycfi::elements::label("Password").text_align(cycfi::elements::canvas::left),
                                            cycfi::elements::hmin_size(200,
                                                cycfi::elements::margin({ 0, 10, 0, 10 },
                                                    m_PasswordEntry.first
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
        ),
        cycfi::elements::box(m_BackgroundColor)
    );
}

void LoginView::UpdateView()
{
    this->InitView();
}

void LoginView::SetLoginCallback(std::function<void(bool)>&& callback)
{
    m_LoginButton.on_click = std::move(callback);
}
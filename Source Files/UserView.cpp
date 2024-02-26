#include "../Header Files/UserView.h"

UserView::UserView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access)
	: View(main_view, user_access)
{

}

void UserView::InitView()
{
    if (m_UserAccess == (uint8_t)AccessType::READ)
    {
        m_AddUserButton.enable(false);
    }

    m_AddUserButton.on_click = [this](bool)
		{
			this->AddUserPopup();
		};

    std::shared_ptr<TableCellComposer> table_cell_composer = std::make_shared<TableCellComposer>(m_UserData, m_UserData.size(), m_UserData[0].size(),
        [&](const std::string& str, uint64_t l, uint64_t c)
        {
            cycfi::elements::color cell_color =
                ((l % 2 == 0) ? cycfi::elements::colors::blue : cycfi::elements::colors::royal_blue)
                .opacity(c % 2 == 0 ? 0.1 : 0.05);


            return cycfi::elements::share(
                cycfi::elements::hsize(200.0f,
                    cycfi::elements::limit({ {100, 50}, {200, 100} },
                        cycfi::elements::layer(
                            cycfi::elements::margin({ 10, 5, 10, 5 },
                                cycfi::elements::align_left_middle(
                                    (l == 0) ?
                                    cycfi::elements::label(str).font_size(15.0f).font(cycfi::elements::get_theme().label_font.extra_bold()) :
                                    cycfi::elements::label(str).font_size(15.0f).font(cycfi::elements::get_theme().label_font)
                                )
                            ),
                            cycfi::elements::box(cell_color)
                        )
                    )
                )
            );
        });

    std::shared_ptr<TableList> table_list = std::make_shared<TableList>(table_cell_composer);

    m_MainView->content(
        cycfi::elements::pane(
            cycfi::elements::htile(
                cycfi::elements::align_left(
                    cycfi::elements::hmax_size(100,
                        m_BackButton
                    )
                ),
                cycfi::elements::align_right(
                    cycfi::elements::hmax_size(100,
                        m_AddUserButton
                    )
                )
            ),
            cycfi::elements::margin({ 10, 10, 10, 10 },
                cycfi::elements::htile(
                    cycfi::elements::align_center_top(
                        cycfi::elements::layer(
                            cycfi::elements::margin({ 10, 10, 10, 10 },
                                cycfi::elements::scroller(
							        cycfi::elements::hold(
								        table_list
							        )
                                )
                            ),
                            cycfi::elements::rbox(m_BackgroundColor.level(1.5f))
                        )
                    )
                )
            )
        ),
        cycfi::elements::box(m_BackgroundColor)
    );
}

void UserView::UpdateView()
{
	this->InitView();
	m_MainView->refresh();
}

void UserView::SetUserData(const std::vector<std::vector<std::string>>& data)
{
	m_UserData = data;
}

void UserView::SetAddUserCallback(std::function<void()> callback)
{
	m_AddUserCallback = callback;
}

void UserView::AddUserPopup()
{
    auto email_input = cycfi::elements::input_box();
    auto first_name_input = cycfi::elements::input_box();
    auto last_name_input = cycfi::elements::input_box();
    auto password_input = cycfi::elements::input_box();

    auto popup = cycfi::elements::dialog1(*m_MainView.get(), 
        cycfi::elements::htile(
            cycfi::elements::scroller(
                cycfi::elements::vtile(
                    cycfi::elements::margin({ 10, 10, 20, 10 },
                        cycfi::elements::vtile(
                            cycfi::elements::align_left(cycfi::elements::label("Email")),
                            cycfi::elements::hsize(200.0f,
                                email_input.first
                            )
                        )
                    ),
                    cycfi::elements::margin({ 10, 10, 20, 10 },
                        cycfi::elements::vtile(
                            cycfi::elements::align_left(cycfi::elements::label("First Name")),
                            cycfi::elements::hsize(200.0f,
                                first_name_input.first
                            )
                        )
                    ),
                    cycfi::elements::margin({ 10, 10, 20, 10 },
                        cycfi::elements::vtile(
                            cycfi::elements::align_left(cycfi::elements::label("Last Name")),
                            cycfi::elements::hsize(200.0f,
                                last_name_input.first
                            )
                        )
                    ),
                    cycfi::elements::margin({ 10, 10, 20, 10 },
                        cycfi::elements::vtile(
                            cycfi::elements::align_left(cycfi::elements::label("Password")),
                            cycfi::elements::hsize(200.0f,
                                password_input.first
                            )
                        )
                    )
                )
            )
        ), m_AddUserCallback, "Add User"
    );

    cycfi::elements::open_popup(popup, *m_MainView.get());
}
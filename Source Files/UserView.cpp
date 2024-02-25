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

    std::vector<std::vector<cycfi::elements::element_ptr >> ptr_list(m_UserData.size());
    for (size_t i = 0; i < m_UserData.size(); i++)
    {
        ptr_list[i].resize(m_UserData[i].size(), nullptr);
    }

    auto&& cell_composer = [](const std::string& str, uint64_t line, uint64_t index)
        {
            cycfi::elements::color cell_color =
                ((line % 2 == 0) ? cycfi::elements::colors::deep_pink : cycfi::elements::colors::royal_blue)
                .opacity(index % 2 == 0 ? 0.1 : 0.05);

            return cycfi::elements::share(
                cycfi::elements::limit({ {100, 50}, {200, 100} },
                    cycfi::elements::layer(
                        cycfi::elements::align_center_middle(
                            cycfi::elements::label(str)
                        ),
                        cycfi::elements::box(cell_color)
                    )
                )
            );
        };

    TableCellComposer table_composer(m_UserData, m_UserData.size(), m_UserData[0].size(), cell_composer);
    TableList table(cycfi::elements::share(table_composer));

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
                cycfi::elements::scroller(
                    cycfi::elements::hold(
                        cycfi::elements::share(table)
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
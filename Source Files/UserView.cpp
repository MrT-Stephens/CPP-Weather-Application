#include "../Header Files/UserView.h"

UserView::UserView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access)
	: View(main_view, user_access)
{
}

void UserView::InitView()
{
    m_MainView->content(
        cycfi::elements::pane(
            cycfi::elements::htile(
                cycfi::elements::align_middle(
                    m_BackButton
                ),
                cycfi::elements::align_right(
                    m_AddUserButton
                )
            ),
            cycfi::elements::scroller(

            )
        )
        cycfi::elements::box(m_BackgroundColor)
    );
}

void UserView::UpdateView()
{
	this->InitView();
	m_MainView->refresh();
}
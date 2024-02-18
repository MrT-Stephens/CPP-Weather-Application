#include "../Header Files/MainView.h"

MainView::MainView(std::shared_ptr<cycfi::elements::window> window)
    : View(window)
{

}

void MainView::InitView()
{
    auto box = cycfi::elements::margin({ 10, 10, 10, 10 }, m_RoundedBox);

    auto menu_button = cycfi::elements::button_menu("Menu", cycfi::elements::menu_position::bottom_left);

    auto menu = cycfi::elements::layer(
        cycfi::elements::vtile(
            cycfi::elements::menu_item("Account"),
            cycfi::elements::menu_item("Settings"),
            cycfi::elements::menu_item("About"),
            cycfi::elements::menu_item("Admin"),
            cycfi::elements::menu_item("Sign Out")
        ), cycfi::elements::panel{}
    );

    menu_button.menu(menu);

    content(
        cycfi::elements::pane(
            cycfi::elements::htile(
                cycfi::elements::align_middle(
                    cycfi::elements::static_text_box("Hello, User!", cycfi::elements::get_theme().text_box_font.size(20.0f))
                ),
                cycfi::elements::align_right(
                    menu_button
                )
            ),
            cycfi::elements::hgrid(
                cycfi::elements::vgrid(
                    box,
                    cycfi::elements::span(2, box)
                ),
                cycfi::elements::vgrid(
                    cycfi::elements::span(2, box),
                    box
                )
            ),
            false
        ),
        cycfi::elements::box(m_BackgroundColor)
    );
}

void MainView::UpdateView()
{

}
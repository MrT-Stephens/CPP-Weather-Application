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
            cycfi::elements::htile(
                cycfi::elements::vtile(
                    cycfi::elements::vstretch(1.0f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Time",
                                cycfi::elements::layer(
                                    cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::label("12:00").font_size(60.0f)
                                            ),
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::label("Monday, 21st January 2022").font_size(20.0f)
                                            )
                                        )
                                    ),
                                    box
                                ), 1.3f, true
                            )
                        )
                    ),
                    cycfi::elements::vstretch(1.5f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Weather",
                                cycfi::elements::layer(
									cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::margin({ 20, 20, 20, 20},
												    cycfi::elements::image("sun.png", 0.4f)
                                                )
											),
                                            cycfi::elements::align_center_middle(
                                                cycfi::elements::htile(
                                                    cycfi::elements::margin({10, 10, 10, 10},
                                                        cycfi::elements::vtile(
                                                            cycfi::elements::label("15:00").font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                cycfi::elements::image("sun.png", 0.05f)
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            cycfi::elements::label("16:00").font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                cycfi::elements::image("sun.png", 0.05f)
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::layer(
                                                        cycfi::elements::margin({ 10, 10, 10, 10 },
                                                            cycfi::elements::vtile(
                                                                cycfi::elements::label("17:00").font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                                cycfi::elements::vspace(5.0f),
                                                                cycfi::elements::align_center(
                                                                    cycfi::elements::image("sun.png", 0.05f)
                                                                )
                                                            )
                                                        ),
                                                        cycfi::elements::rbox(m_BackgroundColor)
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            cycfi::elements::label("18:00").font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                cycfi::elements::image("sun.png", 0.05f)
                                                            )
                                                        )
                                                    ),
                                                    cycfi::elements::margin({ 10, 10, 10, 10 },
                                                        cycfi::elements::vtile(
                                                            cycfi::elements::label("19:00").font_size(20.0f).text_align(cycfi::elements::canvas::center),
                                                            cycfi::elements::vspace(5.0f),
                                                            cycfi::elements::align_center(
                                                                cycfi::elements::image("sun.png", 0.05f)
                                                            )
                                                        )
                                                    )
                                                )
                                            )
										)
                                    ),
									box
								), 1.3f, true
                            )
                        )
                    )
                ),
                cycfi::elements::vtile(
                    cycfi::elements::vstretch(1.5f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Temperature",
                                cycfi::elements::layer(
								    cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center(
                                            cycfi::elements::label("27").font_size(60.0f)
                                            ),
                                            cycfi::elements::align_center_middle(
                                            cycfi::elements::label("Feels like: 25").font_size(20.0f)
                                            )
									    )								
                                    ),
								    box
							    ), 1.3f, true
                            )
                        )
                    ),
                    cycfi::elements::vstretch(1.0f,
                        cycfi::elements::margin({ 10, 10, 10, 10 },
                            cycfi::elements::pane("Humidity",
                                cycfi::elements::layer(
								    cycfi::elements::margin({ 15, 15, 15, 15 },
                                        cycfi::elements::vtile(
                                            cycfi::elements::align_center(
											    cycfi::elements::label("25°C").font_size(60.0f)
										    ),
                                            cycfi::elements::align_center_middle(
											    cycfi::elements::label("Feels like 25°C").font_size(20.0f)
										    )
									    )								
                                    ),
								    box
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

void MainView::UpdateView()
{

}
#pragma once

#include "../Header Files/View.h"
#include "../Header Files/ElementsTable.h"

template <uint64_t ResourceNum = 0>
class UserView : public View
{
public:
	using Button = cycfi::elements::proxy<cycfi::elements::button_styler_gen<cycfi::elements::button_styler_with_body_color<
				   cycfi::elements::button_styler_with_size<cycfi::elements::basic_button_styler>>>, cycfi::elements::basic_button>;
    using AddUserCallback = std::function<void(const std::string& email, const std::string& first_name, const std::string& last_name,
                            const std::string& password, const std::vector<uint8_t>& access_levels)>;
private:
	// Header Buttons
	Button m_BackButton{ cycfi::elements::button("Back") };
	Button m_AddUserButton{ cycfi::elements::button("Add User") };

	// Table
	std::vector<std::vector<std::string>> m_UserData;

	// Add User Data
	std::string m_Email;
	std::string m_FirstName;
	std::string m_LastName;
	std::string m_Password;
	std::array<uint8_t, ResourceNum> m_AccessLevels;

    AddUserCallback m_AddUserCallback;

    void AddUserPopup()
    {
        auto email_input = cycfi::elements::input_box();
        auto first_name_input = cycfi::elements::input_box();
        auto last_name_input = cycfi::elements::input_box();
        auto password_input = cycfi::elements::input_box();

        email_input.second->on_text = [this](std::string_view str)
		    {
			    m_Email = str;
		    };

        first_name_input.second->on_text = [this](std::string_view str)
            {
                m_FirstName = str;
            };

        last_name_input.second->on_text = [this](std::string_view str)
			{
				m_LastName = str;
			};

        password_input.second->on_text = [this](std::string_view str)
            {
                m_Password = str;
            };

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
                        ),
                        GenerateResourceDropDowns()
                    )
                )
            ), [this]() 
            {
                m_AddUserCallback(m_Email, m_FirstName, m_LastName, m_Password, std::vector<uint8_t>(m_AccessLevels.begin(), m_AccessLevels.end()));
            }, "Add User"
        );

        cycfi::elements::open_popup(popup, *m_MainView.get());
    }
	
	cycfi::elements::array_composite<ResourceNum, cycfi::elements::vtile_element> GenerateResourceDropDowns()
	{
		cycfi::elements::array_composite<ResourceNum, cycfi::elements::vtile_element> vtile;

		static const std::string roles[] = { "No Access", "Read", "Write", "Read/Write" };

		for (uint64_t i = 0; i < ResourceNum; ++i)
		{
			vtile[i] = cycfi::elements::share(cycfi::elements::margin({ 10, 10, 20, 10 },
				cycfi::elements::vtile(
					cycfi::elements::align_left(cycfi::elements::label("Resource " + std::to_string(i))),
					cycfi::elements::hsize(200.0f,
						cycfi::elements::selection_menu([this, index = i](std::string_view selected)
							{
								m_AccessLevels[index] = (uint8_t)GetAccessAccessType(selected.data());
							}, roles).first
					)
				)
			));
		}

		return vtile;
	}
public:
	UserView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit)
        : View(main_view, user_access, request_exit), m_AccessLevels({ (uint8_t)AccessType::NO_ACCESS })
    {

    }

    void InitView() override
    {
        if (m_UserAccess == (uint8_t)AccessType::READ)
        {
            m_AddUserButton.enable(false);
        }

        m_AddUserButton.on_click = [this](bool)
            {
                this->AddUserPopup();
            };

        if (m_UserAccess == (uint8_t)AccessType::WRITE)
        {
            m_UserData = {
                m_UserData[0]
            };
		}

        std::shared_ptr<TableCellComposer> table_cell_composer = std::make_shared<TableCellComposer>(m_UserData, m_UserData.size(), m_UserData[0].size(),
            [&](const std::string& str, uint64_t l, uint64_t c)
            {
                cycfi::elements::color cell_color =
                    ((l % 2 == 0) ? cycfi::elements::colors::blue : cycfi::elements::colors::royal_blue).opacity(c % 2 == 0 ? 0.1 : 0.05);

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

    void UpdateView() override
    {
        this->InitView();
        m_MainView->refresh();
    }

    void SetUserData(const std::vector<std::vector<std::string>>& data)
    {
        m_UserData = data;
    }

    void SetAddUserCallback(AddUserCallback callback)
    {
        m_AddUserCallback = callback;
    }

    void SetBackButtonCallback(std::function<void(bool)> callback)
	{
        m_BackButton.on_click = callback;
	}
};
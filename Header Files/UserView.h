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

    /// <summary>
    /// A function which creates a popup for adding a user.
    /// The popup contains input boxes for the user's email, first name, last name, and password.
    /// It also contains dropdowns for the user's access levels to the resources (Views).
    /// The popup also contains a button to add the user.
    /// </summary>
    void AddUserPopup()
    {
        // Initialize input boxes
        auto email_input = cycfi::elements::input_box();
        auto first_name_input = cycfi::elements::input_box();
        auto last_name_input = cycfi::elements::input_box();
        auto password_input = cycfi::elements::input_box();

        // The event handlers for the input boxes, which update the member variables when the text is changed.
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

        // The UI elements for the popup
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

        // Open the popup
        cycfi::elements::open_popup(popup, *m_MainView.get());
    }
	
	/// <summary>
	/// Generates the dropdowns for the user's access levels to the resources (Views).
    /// The dropdowns are generated based on the number of resources (Views) in the system.
    /// The dropdowns contain the access levels: No Access, Read, Write, and Read/Write.
    /// The access levels are stored in the member variable m_AccessLevels.
    /// The access levels are updated when the user selects a different access level from the dropdown.
	/// </summary>
    /// <returns> An array of UI elements for the dropdowns. </returns>
	cycfi::elements::array_composite<ResourceNum, cycfi::elements::vtile_element> GenerateResourceDropDowns()
	{
		cycfi::elements::array_composite<ResourceNum, cycfi::elements::vtile_element> vtile;

		static const std::string roles[] = { "No Access", "Read", "Write", "Read/Write" };

		for (uint64_t i = 0; i < ResourceNum; ++i)
		{
            // The UI elements for an individual dropdown
			vtile[i] = cycfi::elements::share(cycfi::elements::margin({ 10, 10, 20, 10 },
				cycfi::elements::vtile(
					cycfi::elements::align_left(cycfi::elements::label("Resource " + std::to_string(i))),
					cycfi::elements::hsize(200.0f,
                        // The event handler for the dropdown, which updates the member variable when the access level is changed.
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
	/// <summary>
	/// Initalizes a new instance of <see cref="UserView"/> class.
	/// </summary>
    /// <param name="main_view"> A shared pointer to the view which is being displayed on screen. </param>
    /// <param name="user_access"> The users access for this view. </param>
    /// <param name="request_exit"> Function which gets called if the user access is 'NO ACCESS'. </param>
	UserView(std::shared_ptr<cycfi::elements::view> main_view, uint8_t user_access, std::function<void()> request_exit)
        : View(main_view, user_access, request_exit), m_AccessLevels({ (uint8_t)AccessType::NO_ACCESS })
    {

    }

    /// <summary>
    /// Initializes the user view with the required UI elements.
    /// </summary>
    /// <returns> A shared pointer to the UI elements. </returns>
    cycfi::elements::element_ptr InitView() override
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

        // The table cell composer for the user data
        std::shared_ptr<TableCellComposer> table_cell_composer = std::make_shared<TableCellComposer>(m_UserData, m_UserData.size(), m_UserData[0].size(),
            // The function which creates the UI elements for the table cells
            [](const std::string& str, uint64_t l, uint64_t c)
            {
                cycfi::elements::color cell_color =
                    ((l % 2 == 0) ? cycfi::elements::colors::blue : cycfi::elements::colors::royal_blue).opacity(c % 2 == 0 ? 0.1 : 0.05);

                // The UI elements for the table cell
                return cycfi::elements::share(
                    cycfi::elements::hsize(200.0f,
                        cycfi::elements::limit({ {400, 50}, {400, 50} },
                            cycfi::elements::layer(
                                cycfi::elements::margin({ 10, 5, 10, 5 },
                                    cycfi::elements::align_left_middle(
                                        (l == 0) ?
                                        cycfi::elements::label(str.c_str()).font_size(15.0f).font(cycfi::elements::get_theme().label_font.extra_bold()) :
                                        cycfi::elements::label(str.c_str()).font_size(15.0f).font(cycfi::elements::get_theme().label_font)
                                    )
                                ),
                                cycfi::elements::box(cell_color)
                            )
                        )
                    )
                );
            });

        // The table list for the user data
        std::shared_ptr<TableList> table_list = std::make_shared<TableList>(table_cell_composer);

        // The UI elements for the user view
        return cycfi::elements::share(
            cycfi::elements::vtile(
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
                ),
                cycfi::elements::margin({ 10, 10, 10, 10 },
                    cycfi::elements::align_right(
                        cycfi::elements::hmax_size(100,
                            m_AddUserButton
                        )
                    )
                )
            )
        );
    }

    /// <summary>
    /// Sets the user data for the table.
    /// The user data is a 2D vector of strings, where each row represents a user and each column represents a user's attribute.
    /// </summary>
    /// <param name="data"> The user data. </param>
    void SetUserData(const std::vector<std::vector<std::string>>& data)
    {
        m_UserData = data;
    }

    /// <summary>
    /// Sets the callback for adding a user.
    /// The callback is called when the user clicks the 'Add User' button.
    /// </summary>
    /// <param name="callback"> The callback for adding a user. </param>
    void SetAddUserCallback(AddUserCallback callback)
    {
        m_AddUserCallback = callback;
    }
};
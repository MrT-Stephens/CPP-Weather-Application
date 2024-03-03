#include "../Header Files/Controller.h"

Controller::Controller(int argc, char* argv[], std::string name, std::string id)
	: app(argc, argv, name, id), 
	  m_Modal(std::make_unique<Modal>(1)),
	  m_Window(std::make_shared<cycfi::elements::window>(this->name(), cycfi::elements::window::standard, cycfi::elements::rect(50, 50, 1024, 768))),
	  m_CurrentView(nullptr)
{
	m_Window->on_close = [this]()
	{
		this->OnClose();
	};

	m_MainView = std::make_shared<cycfi::elements::view>(*m_Window.get());
}

void Controller::Init()
{
	auto menu_button = cycfi::elements::button_menu("Menu", cycfi::elements::menu_position::bottom_left);

	auto about_menu_item = cycfi::elements::menu_item("About");
	auto data_view_menu_item = cycfi::elements::menu_item("Data View");
	auto users_menu_item = cycfi::elements::menu_item("Users");
	auto sign_out_menu_item = cycfi::elements::menu_item("Sign Out");

	about_menu_item.on_click = [this]()
		{
			if (!m_CurrentSubject.IsEmpty())
			{
				m_IsDataView = false;
				InitAboutView();
			}
		};

	data_view_menu_item.on_click = [this]()
		{
			if (!m_CurrentSubject.IsEmpty())
			{
				m_IsDataView = true;
				InitDataView();
			}
		};

	users_menu_item.on_click = [this]()
		{
			if (!m_CurrentSubject.IsEmpty())
			{
				m_IsDataView = false;
				InitUserView();
			}
		};

	sign_out_menu_item.on_click = [this]()
		{
			if (!m_CurrentSubject.IsEmpty())
			{
				m_IsDataView = false;
				m_CurrentSubject = Subject();
				InitLoginView();
			}
		};

	auto menu = cycfi::elements::layer(
		cycfi::elements::vtile(
			about_menu_item,
			data_view_menu_item,
			users_menu_item,
			sign_out_menu_item
		), cycfi::elements::panel{}
	);

	menu_button.menu(menu);

	m_MainView->content(
		cycfi::elements::pane(
			cycfi::elements::htile(
				cycfi::elements::align_middle(
					cycfi::elements::static_text_box("Hello, User!", cycfi::elements::get_theme().text_box_font.size(20.0f))
				),
				cycfi::elements::align_right(
					cycfi::elements::hmax_size(100,
						menu_button
					)
				)
			),
			cycfi::elements::link(m_MainContent)
		),
		cycfi::elements::box(cycfi::artist::rgba(35, 35, 37, 255))
	);

	InitLoginView();

	this->run();
}

void Controller::InitDataView()
{
	auto [verified, subject] = m_Authenticator.ReAuthenticate(m_CurrentSubject);

	if (verified)
	{ 
		m_CurrentSubject = subject;

		m_CurrentView.reset();
		m_CurrentView = m_ResourceAccessor.AccessResource<DataView>(m_MainView, [this]() { OnClose(); }, m_CurrentSubject, 1);

		auto view = dynamic_cast<DataView*>(m_CurrentView.get());

		if (view != nullptr)
		{
			m_MainContent = view->InitView();
			m_MainView->layout(m_MainContent);

			UpdateDataView();
		}
	}
}

void Controller::InitUserView()
{
	auto [verified, subject] = m_Authenticator.ReAuthenticate(m_CurrentSubject);

	if (verified)
	{
		m_CurrentSubject = subject;

		m_CurrentView.reset();
		m_CurrentView = m_ResourceAccessor.AccessResource<UsersView>(m_MainView, [this]() { OnClose(); }, m_CurrentSubject, 2);

		auto view = dynamic_cast<UsersView*>(m_CurrentView.get());

		if (view != nullptr)
		{
			auto data = m_Authenticator.GetSubjects();

			std::vector<std::vector<std::string>> user_data;

			const auto permissions = m_ResourceAccessor.GetResourceAccesses();

			user_data.push_back({ "Email Address", "First Name", "Last Name" });

			for (uint64_t i = 0; i < permissions.cbegin()->second.size(); ++i)
			{
				user_data[0].push_back("Resource " + std::to_string(i));
			}

			for (const auto& subject : data)
			{
				user_data.push_back({ subject.GetEmail(), subject.GetFirstName(), subject.GetLastName() });
			}

			for (const auto& [key, value] : permissions)
			{
				auto it = std::find_if(user_data.begin(), user_data.end(), [key](const auto& data)
					{
						return data[0] == key;
					});

				if (it != user_data.end())
				{
					for (uint64_t i = 0; i < value.size(); ++i)
					{
						it->push_back(GetAccessString((AccessType)value[i]));
					}
				}
			}

			view->SetUserData(user_data);

			view->SetAddUserCallback([this](
				const std::string& email,
				const std::string& first_name,
				const std::string& last_name,
				const std::string& password,
				const std::vector<uint8_t>& access_levels)
				{
					m_Authenticator.Register(email, first_name, last_name, password);
					m_ResourceAccessor.AddUserPermission(email, access_levels);

					InitUserView();
				}
			);

			m_MainContent = view->InitView();
			m_MainView->layout(m_MainContent);
		}
	}
}

void Controller::InitLoginView()
{
	m_CurrentView.reset();
	m_CurrentView = std::make_shared<LoginView>(m_MainView, (uint8_t)AccessType::READ_WRITE, [this]() { OnClose(); });

	auto view = dynamic_cast<LoginView*>(m_CurrentView.get());

	if (view != nullptr)
	{
		view->SetLoginCallback([this, view](bool)
			{
				auto [verified, subject] = m_Authenticator.Authenticate(view->GetEmail(), view->GetPassword());

				m_CurrentSubject = subject;

				if (verified)
				{
					auto&& on_click = [this]()
						{
							m_IsDataView = true;
							InitDataView();
						};

					auto popup = cycfi::elements::message_box1(*m_MainView.get(), "You have successfully logged in", cycfi::elements::icons::info, on_click);

					cycfi::elements::open_popup(popup, *m_MainView.get());
				}
				else
				{
					auto&& on_click = []()
						{
							return;
						};

					auto popup = cycfi::elements::message_box1(*m_MainView.get(), "Invalid login infomation", cycfi::elements::icons::info, on_click);

					cycfi::elements::open_popup(popup, *m_MainView.get());
				}
			}
		);

		m_MainContent = view->InitView();

		m_MainView->layout(m_MainContent);
	}
}

void Controller::OnClose()
{
	m_IsDataView = false;
	this->stop();
}

void Controller::InitAboutView()
{
	auto [verified, subject] = m_Authenticator.ReAuthenticate(m_CurrentSubject);

	if (verified)
	{
		m_CurrentSubject = subject;

		m_CurrentView.reset();
		m_CurrentView = m_ResourceAccessor.AccessResource<AboutView>(m_MainView, [this]() { OnClose(); }, m_CurrentSubject, 0);

		auto view = dynamic_cast<AboutView*>(m_CurrentView.get());

		if (view != nullptr)
		{
			m_MainContent = view->InitView();
			m_MainView->layout(m_MainContent);
		}
	}
}

void Controller::UpdateDataView()
{
	auto view = dynamic_cast<DataView*>(m_CurrentView.get());

	if (view != nullptr)
	{
		std::tm now = m_Modal->GetTimeSensor()->Read();

		view->UpdateWeather(
			m_Modal->GetWeatherSensor()->Read(), 
			(int32_t)now.tm_hour
		);
		
		view->UpdateTimeAndDate(
			TimeSensor::FormatTime(now, "%H:%M:%S"), 
			TimeSensor::FormatTime(now, "%A %d - %B %Y")
		);

		view->UpdateHumidity(
			m_Modal->GetHumiditySensor()->GetToday(), 
			m_Modal->GetHumiditySensor()->GetYesterday()
		);

		view->UpdateTemperature(
			m_Modal->GetTempratureSensor()->Read(),
			m_Modal->GetDewPoint(),
			m_Modal->GetFeelsLike(),
			m_Modal->GetTempratureSensor()->GetPreviousValue()
		);

		view->UpdateWind(
			m_Modal->GetWindSensor()->Read(),
			m_Modal->GetWindSensor()->GetWindDirection()
		);

		m_MainContent = view->InitView();
		m_MainView->layout(m_MainContent);
		m_MainView->refresh();

		{
			auto&& on_click = []()
				{
					return;
				};

			if (m_Modal->GetCooler()->CheckTrigger(m_Modal->GetTempratureSensor()->GetPreviousValue()) == ActuatorState::On)
			{
				auto popup = cycfi::elements::message_box1(*m_MainView.get(), "Cooler was turned on!", cycfi::elements::icons::info, on_click);

				cycfi::elements::open_popup(popup, *m_MainView.get());
			}

			if (m_Modal->GetHeater()->CheckTrigger(m_Modal->GetTempratureSensor()->GetPreviousValue()) == ActuatorState::On)
			{
				auto popup = cycfi::elements::message_box1(*m_MainView.get(), "Heater was turned on!", cycfi::elements::icons::info, on_click);

				cycfi::elements::open_popup(popup, *m_MainView.get());
			}

			if (m_Modal->GetWindTurbine()->CheckTrigger(m_Modal->GetHumiditySensor()->GetPreviousValue()) == ActuatorState::On)
			{
				auto popup = cycfi::elements::message_box1(*m_MainView.get(), "Wind turbine breaks have been activated!", cycfi::elements::icons::info, on_click);

				cycfi::elements::open_popup(popup, *m_MainView.get());
			}
		}

		if (m_IsDataView)
		{
			// Creates a recursive call to update the data view with new data.
			m_MainView->post(m_Modal->GetSampleRate(), [this]()
				{
					UpdateDataView();
				});
		}
	}
}
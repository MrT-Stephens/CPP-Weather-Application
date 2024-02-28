#include "../Header Files/Controller.h"

Controller::Controller(int argc, char* argv[], std::string name, std::string id)
	: app(argc, argv, name, id), 
	  m_Modal(std::make_unique<Modal>(5U)),
	  m_Window(std::make_shared<cycfi::elements::window>(this->name())),
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
		m_CurrentView = m_ResourceAccessor.AccessResource<DataView>(m_MainView, [this]() { OnClose(); }, m_CurrentSubject, 0);

		auto view = dynamic_cast<DataView*>(m_CurrentView.get());

		if (view != nullptr)
		{
			view->SetOnUsersMenuItemClicked([this]()
				{
					m_MainView->post(std::chrono::seconds(1), [this]()
						{
							InitUserView();
						});
				}
			);

			view->SetOnSignOutMenuItemClicked([this]()
				{
					m_MainView->post(std::chrono::seconds(1), [this]()
						{
							m_CurrentSubject = Subject();
							InitLoginView();
						});
				}
			);

			view->UpdateView();

			m_IsDataView = true;
			UpdateDataView();
		}
	}
}

void Controller::InitUserView()
{
	m_IsDataView = false;

	auto [verified, subject] = m_Authenticator.ReAuthenticate(m_CurrentSubject);

	if (verified)
	{
		m_CurrentSubject = subject;

		m_CurrentView.reset();
		m_CurrentView = m_ResourceAccessor.AccessResource<UsersView>(m_MainView, [this]() { OnClose(); }, m_CurrentSubject, 1);

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

			for (auto& subject : data)
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

					m_MainView->post(std::chrono::seconds(1), [this]()
						{
							InitUserView();
						});
				}
			);

			view->SetBackButtonCallback([this](bool)
				{
					m_MainView->post(std::chrono::seconds(1), [this]()
						{
							InitDataView();
						});
				}
			);

			view->UpdateView();
		}
	}
}

void Controller::InitLoginView()
{
	m_IsDataView = false;
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
							m_MainView->post(std::chrono::seconds(1), [this]()
								{
									InitDataView();
								});
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

		view->UpdateView();
	}
}

void Controller::OnClose()
{
	m_IsDataView = false;
	this->stop();
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
			TimeSensor::FormatTime(now, "%H:%M"), 
			TimeSensor::FormatTime(now, "%A %d - %B %Y")
		);

		view->UpdateHumidity(
			m_Modal->GetHumiditySensor()->GetToday(), 
			m_Modal->GetHumiditySensor()->GetYesterday()
		);

		view->UpdateView();

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
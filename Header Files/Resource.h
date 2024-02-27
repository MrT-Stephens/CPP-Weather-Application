#pragma once

#include "../Header Files/NoCopy.h"
#include "../Header Files/Subject.h"
#include "../Header Files/Permission.h"

#include <elements.hpp>

template <typename... Types>
class Resource : private NoCopy
{
private:
	Permission<Types...> m_Permission;
public:
	Resource()
	{

	}

	template<typename View>
	std::shared_ptr<View> AccessResource(std::shared_ptr<cycfi::elements::view> main_view, std::function<void()> request_exit_func, const Subject& subject, uint32_t resource_id = 0)
	{
		uint8_t user_permission = (uint8_t)m_Permission.CheckPermission(subject.GetEmail(), resource_id);

		return std::make_shared<View>(main_view, user_permission, request_exit_func);
	}

	void AddUserPermission(const std::string& email, const std::vector<uint8_t>& access_levels)
	{
		m_Permission.AddPermissions(email, access_levels);
	}

	const std::unordered_map<std::string, typename Permission<Types...>::Resources>& GetResourceAccesses() const
	{
		return m_Permission.GetResourceAccesses();
	}
};

inline std::string GetAccessString(AccessType access)
{
	switch (access)
	{
	case AccessType::NO_ACCESS:
		return "No Access";
	case AccessType::READ:
		return "Read";
	case AccessType::WRITE:
		return "Write";
	case AccessType::READ_WRITE:
		return "Read/Write";
	default:
		return "No Access";
	}
}

inline AccessType GetAccessAccessType(const std::string& access)
{
	if (access == "Read")
		return AccessType::READ;
	else if (access == "Write")
		return AccessType::WRITE;
	else if (access == "Read/Write")
		return AccessType::READ_WRITE;
	else
		return AccessType::NO_ACCESS;
}
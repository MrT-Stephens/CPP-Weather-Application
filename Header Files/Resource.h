#pragma once

#include "../Header Files/NoCopy.h"
#include "../Header Files/Subject.h"
#include "../Header Files/Permission.h"

#include <elements.hpp>

/// <summary>
/// Resource class that is used to manage access to the resources (Views) in the application.
/// It is a template class that takes in the types of views that are to be managed.
/// </summary>
/// <typeparam name="Types"> The types of views that are to be managed. </typeparam>
template <typename... Types>
class Resource : private NoCopy
{
private:
	Permission<Types...> m_Permission;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Resource"/> class.
	/// </summary>
	Resource()
	{

	}

	/// <summary>
	/// Will first check if the user has access to the resource.
	/// If the user has access, it will create a new view and return it.
	/// </summary>
	/// <typeparam name="View"> The type of view that is to be created. </typeparam>
	/// <param name="main_view"> The main view that the new view will be added to. </param>
	/// <param name="request_exit_func"> The function that will be called when the view is to be exited. </param>
	/// <param name="subject"> The subject that is trying to access the resource. </param>
	/// <param name="resource_id"> The id of the resource that is to be accessed. </param>
	/// <returns> A shared pointer to the new view. </returns>
	template<typename View>
	std::shared_ptr<View> AccessResource(std::shared_ptr<cycfi::elements::view> main_view, std::function<void()> request_exit_func, const Subject& subject, uint32_t resource_id = 0)
	{
		uint8_t user_permission = (uint8_t)m_Permission.CheckPermission(subject.GetEmail(), resource_id);

		return std::make_shared<View>(main_view, user_permission, request_exit_func);
	}

	/// <summary>
	/// Adds a new user permission to the permission list.
	/// </summary>
	/// <param name="email"> The email of the user that is to be added. </param>
	/// <param name="access_levels"> The access levels that the user is to be given. </param>
	void AddUserPermission(const std::string& email, const std::vector<uint8_t>& access_levels)
	{
		m_Permission.AddPermissions(email, access_levels);
	}

	const std::unordered_map<std::string, typename Permission<Types...>::Resources>& GetResourceAccesses() const
	{
		return m_Permission.GetResourceAccesses();
	}
};

/// <summary>
/// Gets the string representation of the access type.
/// </summary>
/// <param name="access"> The access type that is to be converted to a string. </param>
/// <returns> The string representation of the access type. </returns>
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

/// <summary>
/// Gets the access type from the string representation of the access type.
/// </summary>
/// <param name="access"> The string representation of the access type. </param>
/// <returns> The access type. </returns>
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
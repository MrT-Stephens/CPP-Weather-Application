#pragma once

#include "../Header Files/NoCopy.h"
#include "../Header Files/Storage.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <any>
#include <memory>

/// <summary>
/// Access type for the resources
/// NO_ACCESS - No access to the resource
/// READ - Read access to the resource
/// WRITE - Write access to the resource
/// READ_WRITE - Read and write access to the resource
/// </summary>
enum class AccessType : uint8_t
{
	NO_ACCESS = 0x00,
	READ = 0x01,
	WRITE = 0x02,
	READ_WRITE = READ | WRITE
};

/// <summary>
/// Permission class to manage the access to the resources (Views).
/// </summary>
/// <typeparam name="...T"> Used to pass in all the different views this class will manage. </typeparam>
template <typename... T>
class Permission : private NoCopy
{
public:
	using Resources = std::vector<uint8_t>;
private:
	std::unordered_map<std::string, Resources> m_ResourceAccess;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Permission"/> class.
	/// Reads the users resource accesses from the storage.
	/// If the resource accesses are not found, it creates a new one.
	/// </summary>
	Permission()
	{
		if (!Storage::Read(std::to_string(typeid(this).hash_code()), m_ResourceAccess))
		{
			m_ResourceAccess.insert(std::make_pair("admin@admin.com", Resources(sizeof...(T), (uint8_t)AccessType::READ_WRITE)));
		}
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="Permission"/> class.
	/// Writes the users resource accesses to the storage.
	/// </summary>
	~Permission()
	{
		Storage::Write(std::to_string(typeid(this).hash_code()), m_ResourceAccess);
	}

	/// <summary>
	/// Checks the permission for the given email and resource id.
	/// If the email is not found, it returns NO_ACCESS.
	/// If the resource id is not found, it returns NO_ACCESS.
	/// Otherwise, it returns the access type for the given email and resource id.
	/// </summary>
	/// <param name="email"> The users email. </param>
	/// <param name="resource_id"> The resource id the users is accessing. </param>
	/// <returns> The access type for the given email and resource id. </returns>
	AccessType CheckPermission(const std::string& email, uint32_t resource_id)
	{
		std::unordered_map<std::string, Resources>::iterator it = m_ResourceAccess.find(email);

		if (it != m_ResourceAccess.end() && resource_id <= it->second.size())
		{
			return (AccessType)it->second[resource_id];
		}

		return AccessType::NO_ACCESS;
	}

	/// <summary>
	/// Adds the permissions for the given email and resources.
	/// </summary>
	/// <param name="email"> The users email. </param>
	/// <param name="resources"> The resources the user has access to. </param>
	void AddPermissions(const std::string& email, const Resources& resources)
	{
		m_ResourceAccess.insert(std::make_pair(email, resources));
	}

	const std::unordered_map<std::string, Resources>& GetResourceAccesses() const
	{
		return m_ResourceAccess;
	}
};
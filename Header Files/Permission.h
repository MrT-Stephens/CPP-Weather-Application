#pragma once

#include "../Header Files/NoCopy.h"
#include "../Header Files/Storage.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <any>
#include <memory>

enum class AccessType : uint8_t
{
	NO_ACCESS = 0x00,
	READ = 0x01,
	WRITE = 0x02,
	READ_WRITE = READ | WRITE
};

template <typename... T>
class Permission : private NoCopy
{
public:
	using Resources = std::vector<uint8_t>;
private:
	std::unordered_map<std::string, Resources> m_ResourceAccess;
public:
	Permission()
	{
		if (!Storage::Read(std::to_string(typeid(this).hash_code()), m_ResourceAccess))
		{
			m_ResourceAccess.insert(std::make_pair("admin@admin.com", Resources(sizeof...(T), (uint8_t)AccessType::READ_WRITE)));
		}
	}

	~Permission()
	{
		Storage::Write(std::to_string(typeid(this).hash_code()), m_ResourceAccess);
	}

	AccessType CheckPermission(const std::string& email, uint32_t resource_id)
	{
		std::unordered_map<std::string, Resources>::iterator it = m_ResourceAccess.find(email);

		if (it != m_ResourceAccess.end() && resource_id <= it->second.size())
		{
			return (AccessType)it->second[resource_id];
		}

		return AccessType::NO_ACCESS;
	}

	void AddPermissions(const std::string& email, const Resources& resources)
	{
		m_ResourceAccess.insert(std::make_pair(email, resources));
	}

	const std::unordered_map<std::string, Resources>& GetResourceAccesses() const
	{
		return m_ResourceAccess;
	}
};
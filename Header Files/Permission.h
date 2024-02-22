#pragma once

#include "../Header Files/NoCopy.h"

#include <string>
#include <vector>
#include <unordered_map>

enum class AccessType : uint8_t
{
	NO_ACCESS = 0x00,
	READ = 0x01,
	WRITE = 0x02,
	READ_WRITE = 0x04
};

class Permission : private NoCopy
{
public:
	using Resources = std::vector<uint8_t>;
private:
	std::unordered_map<std::string, Resources> m_ResourceAccess;
public:
	Permission()
	{

	}

	~Permission()
	{

	}

	uint8_t CheckPermission(const std::string& email, uint32_t resource_id)
	{
		std::unordered_map<std::string, Resources>::iterator it = m_ResourceAccess.find(email);

		if (it != m_ResourceAccess.end() && resource_id <= it->second.size())
		{
			return it->second[resource_id];
		}

		return (uint8_t)AccessType::NO_ACCESS;
	}
};
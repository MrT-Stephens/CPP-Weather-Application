#pragma once

#include "../Header Files/Storage.h"
#include "../Header Files/NoCopy.h"

#include <string>
#include <unordered_map>

class AuthenticatorInfo : private NoCopy
{
private:
	std::unordered_map<std::string, std::string> m_AuthenticatorInfo;
public:
	AuthenticatorInfo()
	{
		if (!Storage::Read(std::to_string(typeid(this).hash_code()), m_AuthenticatorInfo))
		{
			m_AuthenticatorInfo.insert(std::make_pair("admin@admin.com", "admin"));
		}
	}

	~AuthenticatorInfo()
	{
		Storage::Write(std::to_string(typeid(this).hash_code()), m_AuthenticatorInfo);

		m_AuthenticatorInfo.clear();
	}

	bool ValidateSubject(const std::string& email, const std::string& password)
	{
		std::unordered_map<std::string, std::string>::const_iterator it = m_AuthenticatorInfo.find(email);

		if (it != m_AuthenticatorInfo.end())
		{
			if (it->second == password)
			{
				return true;
			}
		}

		return false;
	}

	void AddSubject(const std::string& email, const std::string& password)
	{
		std::unordered_map<std::string, std::string>::const_iterator it = m_AuthenticatorInfo.find(email);

		if (it == m_AuthenticatorInfo.end())
		{
			m_AuthenticatorInfo.insert(std::make_pair(email, password));
		}
	}
};
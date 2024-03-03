#pragma once

#include "../Header Files/Storage.h"
#include "../Header Files/NoCopy.h"

#include <string>
#include <unordered_map>

/// <summary>
/// This class is responsible for managing the authenticator information.
/// It manages the email and password of the users.
/// </summary>
class AuthenticatorInfo : private NoCopy
{
private:
	std::unordered_map<std::string, std::string> m_AuthenticatorInfo;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AuthenticatorInfo"/> class.
	/// It reads the authenticator information from the storage.
	/// </summary>
	AuthenticatorInfo()
	{
		if (!Storage::Read(std::to_string(typeid(this).hash_code()), m_AuthenticatorInfo))
		{
			m_AuthenticatorInfo.insert(std::make_pair("admin@admin.com", "admin"));
		}
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="AuthenticatorInfo"/> class.
	/// It writes the authenticator information to the storage.
	/// </summary>
	~AuthenticatorInfo()
	{
		Storage::Write(std::to_string(typeid(this).hash_code()), m_AuthenticatorInfo);

		m_AuthenticatorInfo.clear();
	}

	/// <summary>
	/// Validates the subject based on the email and password that are provided.
	/// </summary>
	/// <param name="email"> The users email. </param>
	/// <param name="password"> The users password. </param>
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

	/// <summary>
	/// Adds the subject based on the email and password that are provided.
	/// </summary>
	/// <param name="email"> The users email. </param>
	/// <param name="password"> The users password. </param>
	void AddSubject(const std::string& email, const std::string& password)
	{
		std::unordered_map<std::string, std::string>::const_iterator it = m_AuthenticatorInfo.find(email);

		if (it == m_AuthenticatorInfo.end())
		{
			m_AuthenticatorInfo.insert(std::make_pair(email, password));
		}
	}
};
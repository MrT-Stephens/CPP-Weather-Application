#pragma once

#include <string>
#include <regex>

namespace str_utils
{
	/// <summary>
	/// Removes all leading and trailing charater from the string.
	/// </summary>
	/// <param name="str"> The string to trim. </param>
	/// <param name="trim_char"> The character to remove. </param>
	inline void Trim(std::string& str, char trim_char = ' ')
	{
		size_t start = str.find_first_not_of(trim_char);
		size_t end = str.find_last_not_of(trim_char);

		if (start == std::string::npos || end == std::string::npos)
		{
			str = "";
		}
		else
		{
			str = str.substr(start, end - start + 1);
		}
	}

	/// <summary>
	/// Removes all leading charater from the string.
	/// </summary>
	/// <param name="str"> The string to trim. </param>
	/// <param name="trim_char"> The character to remove. </param>
	inline void TrimStart(std::string& str, char trim_char = ' ')
	{
		size_t start = str.find_first_not_of(trim_char);

		if (start == std::string::npos)
		{
			str = "";
		}
		else
		{
			str = str.substr(start);
		}
	}

	/// <summary>
	/// Removes all trailing charater from the string.
	/// </summary>
	/// <param name="str"> The string to trim. </param>
	/// <param name="trim_char"> The character to remove. </param>
	inline void TrimEnd(std::string& str, char trim_char = ' ')
	{
		size_t end = str.find_last_not_of(trim_char);

		if (end == std::string::npos)
		{
			str = "";
		}
		else
		{
			str = str.substr(0, end + 1);
		}
	}

	/// <summary>
	/// Replaces all instances of old_char with new_char in the string.
	/// </summary>
	/// <param name="str"> The string to modify. </param>
	/// <param name="old_char"> The character to replace. </param>
	/// <param name="new_char"> The character to replace with. </param>
	inline void Replace(std::string& str, char old_char, char new_char)
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == old_char)
			{
				str[i] = new_char;
			}
		}
	}

	// Regexes for validating email and password
	inline const std::regex EmailRegex = std::regex("^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$");
	inline const std::regex PasswordRegex = std::regex("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d!@#$%^&*()-_=+]{8,}$");
}
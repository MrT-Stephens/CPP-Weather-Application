#pragma once

#include "../Header Files/Xml.h"
#include "../Header Files/Subject.h"
#include "../Header Files/NoCopy.h"

#include <filesystem>
#include <unordered_map>
#include <vector>

class Storage : private NoCopy
{
private:
	static Storage s_Instance;

	std::string m_CurrentDirectory;
	std::string m_Key;

	Storage();

	bool WriteInternal(const std::string& name, const std::unordered_map<std::string, std::string>& data);
	bool ReadInternal(const std::string& name, std::unordered_map<std::string, std::string>& data);

	bool WriteInternal(const std::string& name, const std::vector<Subject>& data);
	bool ReadInternal(const std::string& name, std::vector<Subject>& data);

	bool WriteInternal(const std::string& name, const std::unordered_map<std::string, std::vector<uint8_t>>& data);
	bool ReadInternal(const std::string& name, std::unordered_map<std::string, std::vector<uint8_t>>& data);

	std::string Encrypt(const std::string& data, const std::string& key);
	std::string Decrypt(const std::string& data, const std::string& key);
public:
	static Storage& Get() { return s_Instance; }

	static bool Write(const std::string& name, const std::unordered_map<std::string, std::string>& data)
	{
		return s_Instance.WriteInternal(name, data);
	}

	static bool Read(const std::string& name, std::unordered_map<std::string, std::string>& data)
	{
		return s_Instance.ReadInternal(name, data);
	}

	static bool Write(const std::string& name, const std::vector<Subject>& data)
	{
		return s_Instance.WriteInternal(name, data);
	}

	static bool Read(const std::string& name, std::vector<Subject>& data)
	{
		return s_Instance.ReadInternal(name, data);
	}

	static bool Write(const std::string& name, const std::unordered_map<std::string, std::vector<uint8_t>>& data)
	{
		return s_Instance.WriteInternal(name, data);
	}

	static bool Read(const std::string& name, std::unordered_map<std::string, std::vector<uint8_t>>& data)
	{
		return s_Instance.ReadInternal(name, data);
	}
};
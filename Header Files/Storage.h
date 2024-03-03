#pragma once

#include "../Header Files/Xml.h"
#include "../Header Files/Subject.h"
#include "../Header Files/NoCopy.h"

#include <filesystem>
#include <unordered_map>
#include <vector>

/// <summary>
/// Storage class is a singleton class that is used to read and write data to the disk.
/// It is used to store all the data that is used by the application.
/// It will store the data in the current directory of the application.
/// Also, it will encrypt the data before writing it to the disk and store it in a XML file.
/// </summary>
class Storage : private NoCopy
{
private:
	// The instance of the Storage class.
	static Storage s_Instance;

	// The current directory of the application.
	std::string m_CurrentDirectory;

	// The key that is used to encrypt and decrypt the data.
	std::string m_Key;

	// Private constructor to prevent the creation of the object.
	Storage();

	// Read and write functions that are used to read and write the data to the disk.
	bool WriteInternal(const std::string& name, const std::unordered_map<std::string, std::string>& data);
	bool ReadInternal(const std::string& name, std::unordered_map<std::string, std::string>& data);

	bool WriteInternal(const std::string& name, const std::vector<Subject>& data);
	bool ReadInternal(const std::string& name, std::vector<Subject>& data);

	bool WriteInternal(const std::string& name, const std::unordered_map<std::string, std::vector<uint8_t>>& data);
	bool ReadInternal(const std::string& name, std::unordered_map<std::string, std::vector<uint8_t>>& data);

	// Encrypt and decrypt functions that are used to encrypt and decrypt the data.
	std::string Encrypt(const std::string& data, const std::string& key);
	std::string Decrypt(const std::string& data, const std::string& key);
public:
	// Get the instance of the Storage class.
	static Storage& Get() { return s_Instance; }

	// Static read and write functions which call the internal read and write functions.
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
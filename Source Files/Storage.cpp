#include "../Header Files/Storage.h"
#include "../lib/easy-encryption/encryption.h"

/// <summary>
/// Initializes a new instance of the <see cref="Storage"/> class.
/// Sets the current directory to the current working directory.
/// Also generates a key for the encryption and decryption of data.
/// </summary>
Storage::Storage()
	: m_CurrentDirectory(std::filesystem::current_path().string())
{
	std::string key = std::to_string(typeid(this).hash_code());

	for (char& c : key)
	{
		c = (char)('a' + (c - '0'));
	}

	m_Key = key;
}

/// <summary>
/// Initializes a new instance of the <see cref="Storage"/> class.
/// </summary>
Storage Storage::s_Instance;

/// <summary>
/// Encrypts the specified data using the specified key.
/// </summary>
/// <param name="data"> The data to encrypt. </param>
/// <param name="key"> The key to use for encryption. </param>
/// <returns> The encrypted data. </returns>
std::string Storage::Encrypt(const std::string& data, const std::string& key)
{
	std::string data_i{ data }, key_i{ key };
	return encrypt(data_i, key_i);
}

/// <summary>
/// Decrypts the specified data using the specified key.
/// </summary>
/// <param name="data"> The data to decrypt. </param>
/// <param name="key"> The key to use for decryption. </param>
/// <returns> The decrypted data. </returns>
std::string Storage::Decrypt(const std::string& data, const std::string& key)
{
	std::string data_i{ data }, key_i{ key };
	return decrypt(data_i, key_i);
}

/// <summary>
/// Writes the <see cref="AuthenticationInfo"/> to the specified file.
/// Uses the <see cref="mrt::Xml"/> class to write the data to the file.
/// </summary>
/// <param name="name"> The name of the file to write to. </param>
/// <param name="data"> The data to write to the file. </param>
/// <returns> True if the data was written successfully, otherwise false. </returns>
bool Storage::WriteInternal(const std::string& name, const std::unordered_map<std::string, std::string>& data)
{
	mrt::XML_Node root(name);

	for (const auto& [key, value] : data)
	{
		mrt::XML_Node node("user");
		node.AddChild(mrt::XML_Node("email", Encrypt(key, m_Key)));
		node.AddChild(mrt::XML_Node("password", Encrypt(value, m_Key)));
		root.AddChild(node);
	}

	mrt::XML_Document doc(root, "1.0");

	return (doc.WriteDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) == mrt::XML_Document_FileError::SUCCESS) ? true : false;
}

/// <summary>
/// Reads the <see cref="AuthenticationInfo"/> from the specified file.
/// Uses the <see cref="mrt::Xml"/> class to read the data from the file.
/// </summary>
/// <param name="name"> The name of the file to read from. </param>
/// <param name="data"> The data to read from the file. </param>
/// <returns> True if the data was read successfully, otherwise false. </returns>
bool Storage::ReadInternal(const std::string& name, std::unordered_map<std::string, std::string>& data)
{
	mrt::XML_Document doc;

	if (doc.ReadDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) != mrt::XML_Document_FileError::SUCCESS)
		return false;

	mrt::XML_Node root = doc.GetRoot();

	for (const auto& node : root.GetAllChildren())
	{
		data.insert(std::make_pair(Decrypt(node.GetChild(0).GetValue(), m_Key), Decrypt(node.GetChild(1).GetValue(), m_Key)));
	}

	return true;
}

/// <summary>
/// Writes the <see cref="SubjectInfo"/> to the specified file.
/// Uses the <see cref="mrt::Xml"/> class to write the data to the file.
/// </summary>
/// <param name="name"> The name of the file to write to. </param>
/// <param name="data"> The data to write to the file. </param>
/// <returns> True if the data was written successfully, otherwise false. </returns>
bool Storage::WriteInternal(const std::string& name, const std::vector<Subject>& data)
{
	mrt::XML_Node root(name);

	for (const auto& subject : data)
	{
		mrt::XML_Node node("subject");
		node.AddChild(mrt::XML_Node("email", Encrypt(subject.GetEmail(), m_Key)));
		node.AddChild(mrt::XML_Node("firstname", Encrypt(subject.GetFirstName(), m_Key)));
		node.AddChild(mrt::XML_Node("lastname", Encrypt(subject.GetLastName(), m_Key)));
		root.AddChild(node);
	}

	mrt::XML_Document doc(root, "1.0");

	return (doc.WriteDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) == mrt::XML_Document_FileError::SUCCESS) ? true : false;
}

/// <summary>
/// Reads the <see cref="SubjectInfo"/> from the specified file.
/// Uses the <see cref="mrt::Xml"/> class to read the data from the file.
/// </summary>
/// <param name="name"> The name of the file to read from. </param>
/// <param name="data"> The data to read from the file. </param>
/// <returns> True if the data was read successfully, otherwise false. </returns>
bool Storage::ReadInternal(const std::string& name, std::vector<Subject>& data)
{
	mrt::XML_Document doc;

	if (doc.ReadDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) != mrt::XML_Document_FileError::SUCCESS)
		return false;

	mrt::XML_Node root = doc.GetRoot();

	for (const auto& node : root.GetAllChildren())
	{
		data.emplace_back(Decrypt(node.GetChild(0).GetValue(), m_Key), Decrypt(node.GetChild(1).GetValue(), m_Key), Decrypt(node.GetChild(2).GetValue(), m_Key));
	}

	return true;
}

/// <summary>
/// Writes the <see cref="Permissions"/> to the specified file.
/// Uses the <see cref="mrt::Xml"/> class to write the data to the file.
/// </summary>
/// <param name="name"> The name of the file to write to. </param>
/// <param name="data"> The data to write to the file. </param>
/// <returns> True if the data was written successfully, otherwise false. </returns>
bool Storage::WriteInternal(const std::string& name, const std::unordered_map<std::string, std::vector<uint8_t>>& data)
{
	mrt::XML_Node root(name);

	for (const auto& [key, value] : data)
	{
		mrt::XML_Node node("user");
		node.AddChild(mrt::XML_Node("email", Encrypt(key, m_Key)));

		for (uint64_t i = 0; i < value.size(); ++i)
		{
			mrt::XML_Node subNode(std::to_string(i), std::to_string(value[i]));
			node.AddChild(subNode);
		}

		root.AddChild(node);
	}

	mrt::XML_Document doc(root, "1.0");

	return (doc.WriteDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) == mrt::XML_Document_FileError::SUCCESS) ? true : false;
}

/// <summary>
/// Reads the <see cref="Permissions"/> from the specified file.
/// Uses the <see cref="mrt::Xml"/> class to read the data from the file.
/// </summary>
/// <param name="name"> The name of the file to read from. </param>
/// <param name="data"> The data to read from the file. </param>
/// <returns> True if the data was read successfully, otherwise false. </returns>
bool Storage::ReadInternal(const std::string& name, std::unordered_map<std::string, std::vector<uint8_t>>& data)
{
	mrt::XML_Document doc;

	if (doc.ReadDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) != mrt::XML_Document_FileError::SUCCESS)
		return false;

	mrt::XML_Node root = doc.GetRoot();

	for (const auto& children : root.GetAllChildren())
	{
		std::string key;
		std::vector<uint8_t> vec;

		for (uint64_t i = 0; i < children.GetChildCount(); ++i)
		{
			if (i == 0)
			{
				key = Decrypt(children.GetChild(i).GetValue(), m_Key);
				continue;
			}

			vec.push_back((uint8_t)std::stoul(children.GetChild(i).GetValue()));
		}

		data.insert(std::make_pair(key, vec));
	}

	return true;
}
#include "../Header Files/Storage.h"

Storage::Storage()
	: m_CurrentDirectory(std::filesystem::current_path().string())
{
	std::string key = std::to_string(typeid(this).hash_code());

	for (char& c : key)
	{
		c = (char)((int)c + (int)'a');
	}

	m_Key = key;
}

Storage Storage::s_Instance;

std::string Storage::Encrypt(const std::string& data, const std::string& key)
{
	std::string text = "";

	uint64_t keyLength = key.length();

	for (uint64_t i = 0; i < data.length(); ++i) 
	{
		char c = data[i];

		char shift = key[i % keyLength];

		if (isalpha(c)) 
		{
			char base = islower(c) ? 'a' : 'A';
			char shiftedChar = static_cast<char>((c - base - (tolower(shift) - 'a') + 26) % 26 + base);
			text += shiftedChar;
		}
		else 
		{
			text += c;
		}
	}
	return text;
}

std::string Storage::Decrypt(const std::string& data, const std::string& key)
{
	std::string text = "";

	uint64_t keyLength = key.length();

	for (uint64_t i = 0; i < data.length(); ++i)
	{
		char c = data[i];

		char shift = key[i % keyLength];

		if (isalpha(c))
		{
			char base = islower(c) ? 'a' : 'A';
			char shiftedChar = static_cast<char>((c - base - (tolower(shift) - 'a') + 26) % 26 + base);
			text += shiftedChar;
		}
		else
		{
			text += c;
		}
	}

	return text;
}

bool Storage::WriteInternal(const std::string& name, const std::unordered_map<std::string, std::string>& data)
{
	mrt::XML_Node root(name);

	for (const auto& [key, value] : data)
	{
		mrt::XML_Node node("user");
		node.AddAttribute("email", Encrypt(key, m_Key));
		node.AddAttribute("password", Encrypt(value, m_Key));
		root.AddChild(node);
	}

	mrt::XML_Document doc(root, "1.0");

	return (doc.WriteDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) == mrt::XML_Document_FileError::SUCCESS) ? true : false;
}

bool Storage::ReadInternal(const std::string& name, std::unordered_map<std::string, std::string>& data)
{
	mrt::XML_Document doc;

	if (doc.ReadDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) != mrt::XML_Document_FileError::SUCCESS)
		return false;

	mrt::XML_Node root = doc.GetRoot();

	for (const auto& node : root.GetAllChildren())
	{
		data.insert(std::make_pair(Decrypt(node.GetAttribute(0).m_Value, m_Key), Decrypt(node.GetAttribute(1).m_Value, m_Key)));
	}

	return true;
}

bool Storage::WriteInternal(const std::string& name, const std::vector<Subject>& data)
{
	mrt::XML_Node root(name);

	for (const auto& subject : data)
	{
		mrt::XML_Node node("subject");
		node.AddAttribute("email", Encrypt(subject.GetEmail(), m_Key));
		node.AddAttribute("firstname", Encrypt(subject.GetFirstName(), m_Key));
		node.AddAttribute("lastname", Encrypt(subject.GetLastName(), m_Key));
		root.AddChild(node);
	}

	mrt::XML_Document doc(root, "1.0");

	return (doc.WriteDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) == mrt::XML_Document_FileError::SUCCESS) ? true : false;
}

bool Storage::ReadInternal(const std::string& name, std::vector<Subject>& data)
{
	mrt::XML_Document doc;

	if (doc.ReadDocument(m_CurrentDirectory + "\\" + name + ".xml", doc) != mrt::XML_Document_FileError::SUCCESS)
		return false;

	mrt::XML_Node root = doc.GetRoot();

	for (const auto& node : root.GetAllChildren())
	{
		data.emplace_back(Decrypt(node.GetAttribute(0).m_Value, m_Key), Decrypt(node.GetAttribute(1).m_Value, m_Key), Decrypt(node.GetAttribute(2).m_Value, m_Key));
	}

	return true;
}
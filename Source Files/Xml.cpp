#include "../Header Files/Xml.h"

/***************************/
/* XML_Node Implementation */
/***************************/

mrt::XML_Node::XML_Node() : m_Name(), m_Value() { }

mrt::XML_Node::XML_Node(const std::string& name, const std::string& value) : m_Name(name), m_Value(value) { }

mrt::XML_Node::XML_Node(const XML_Node& other) : m_Name(other.m_Name), m_Value(other.m_Value), m_Attributes(other.m_Attributes), m_Children(other.m_Children) { }

mrt::XML_Node::XML_Node(XML_Node&& other) noexcept :
	m_Name(std::forward<std::string>(other.m_Name)),
	m_Value(std::forward<std::string>(other.m_Value)),
	m_Attributes(std::forward<std::vector<XML_Attribute>>(other.m_Attributes)),
	m_Children(std::forward<std::vector<XML_Node>>(other.m_Children)) { }

mrt::XML_Node& mrt::XML_Node::operator=(const XML_Node& other)
{
	m_Name = other.m_Name;
	m_Value = other.m_Value;
	m_Attributes = other.m_Attributes;
	m_Children = other.m_Children;

	return *this;
}

void mrt::XML_Node::SetName(std::string name) { m_Name = name; }

const std::string& mrt::XML_Node::GetName() const { return m_Name; }

void mrt::XML_Node::SetValue(std::string value) { m_Value = value; }

const std::string& mrt::XML_Node::GetValue() const { return m_Value; }

uint64_t mrt::XML_Node::GetChildCount() const { return m_Children.size(); }

uint64_t mrt::XML_Node::GetAttributeCount() const { return m_Attributes.size(); }

mrt::XML_Node& mrt::XML_Node::AddAttribute(const std::string& name, const std::string& value)
{
	m_Attributes.emplace_back(name, value);

	return *this;
}

template <class... Args>
mrt::XML_Node& mrt::XML_Node::EmplaceAttribute(Args&&... args)
{
	m_Attributes.emplace_back(std::forward<Args>(args)...);

	return *this;
}

mrt::XML_Node& mrt::XML_Node::AddChild(const XML_Node& child)
{
	m_Children.emplace_back(child);

	return m_Children.back();
}

template <class... Args>
mrt::XML_Node& mrt::XML_Node::EmplaceChild(Args&&... args)
{
	m_Children.emplace_back(std::forward<Args>(args)...);

	return m_Children.back();
}

mrt::XML_Attribute& mrt::XML_Node::GetAttribute(uint64_t index)
{
	if (index >= m_Attributes.size())
	{
		throw std::out_of_range("Index out of range.");
	}
	else
	{
		return m_Attributes[index];
	}
}

const mrt::XML_Attribute& mrt::XML_Node::GetAttribute(uint64_t index) const
{
	if (index >= m_Attributes.size())
	{
		throw std::out_of_range("Index out of range.");
	}
	else
	{
		return m_Attributes[index];
	}
}

mrt::XML_Node& mrt::XML_Node::GetChild(uint64_t index)
{
	if (index >= m_Children.size())
	{
		throw std::out_of_range("Index out of range.");
	}
	else
	{
		return m_Children[index];
	}
}

const mrt::XML_Node& mrt::XML_Node::GetChild(uint64_t index) const
{
	if (index >= m_Children.size())
	{
		throw std::out_of_range("Index out of range.");
	}
	else
	{
		return m_Children[index];
	}
}

std::vector<mrt::XML_Attribute>& mrt::XML_Node::GetAllAttributes() { return m_Attributes; }

const std::vector<mrt::XML_Attribute>& mrt::XML_Node::GetAllAttributes() const { return m_Attributes; }

std::vector<mrt::XML_Node>& mrt::XML_Node::GetAllChildren() { return m_Children; }

const std::vector<mrt::XML_Node>& mrt::XML_Node::GetAllChildren() const { return m_Children; }

/*******************************/
/* XML_Document Implementation */
/*******************************/

mrt::XML_Document::XML_Document() : m_Version("1.0") { }

mrt::XML_Document::XML_Document(const std::string& version) :
	m_Version(version) { }

mrt::XML_Document::XML_Document(const XML_Node& root, const std::string& version) :
	m_Root(root), m_Version(version) { }

mrt::XML_Document::XML_Document(const XML_Document& other) :
	m_Version(other.m_Version), m_Root(other.m_Root) { }

mrt::XML_Document::XML_Document(XML_Document&& other) noexcept :
	m_Version(std::forward<std::string>(other.m_Version)),
	m_Root(std::forward<XML_Node>(other.m_Root)) { }

mrt::XML_Document& mrt::XML_Document::operator=(const XML_Document& other)
{
	m_Version = other.m_Version;
	m_Root = other.m_Root;

	return *this;
}

mrt::XML_Node& mrt::XML_Document::GetRoot() { return m_Root; }

const mrt::XML_Node& mrt::XML_Document::GetRoot() const { return m_Root; }

std::string& mrt::XML_Document::GetVersion() { return m_Version; }

const std::string& mrt::XML_Document::GetVersion() const { return m_Version; }

mrt::XML_Document_FileError mrt::XML_Document::ReadDocument(const std::string& path, XML_Document& document)
{
	std::ifstream fs(path, std::ios::in);

	if (!fs.is_open())
	{
		return XML_Document_FileError::FAILED_TO_OPEN;
	}

	{
		std::string inputString((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

		inputString.erase(std::remove_if(inputString.begin(), inputString.end(), [](char c) { return c == '\n'; }), inputString.end());

		if (inputString.empty())
		{
			return XML_Document_FileError::FILE_EMPTY;
		}

		size_t pos = inputString.find("?>");

		if (pos != std::string::npos)
		{
			pos += 2;

			inputString = inputString.substr(pos);
		}

		mrtInternal::XML_Tokenizer_Parser parser(&document.GetRoot(), inputString.cbegin(), inputString.cend());

		parser.Parse();
	}

	fs.close();
	return XML_Document_FileError::SUCCESS;
}

mrt::XML_Document_FileError mrt::XML_Document::WriteDocument(const std::string& path, const XML_Document& document, bool addProlog, bool newLines)
{
	std::ofstream fs(path, std::ios::out);

	if (!fs.is_open())
	{
		return XML_Document_FileError::FAILED_TO_OPEN;
	}

	if (addProlog)
	{
		fs << getXMLprolog(document.GetVersion()) << getNewLine(newLines);
	}

	fs << getStartNode(document.GetRoot()) << getNewLine(newLines);

	WriteChildrenNodes(&fs, document.GetRoot(), newLines);

	fs << getEndNode(document.GetRoot()) << getNewLine(newLines);

	fs.close();
	return XML_Document_FileError::SUCCESS;
}

void mrt::XML_Document::WriteChildrenNodes(std::ostream* fs, const XML_Node& node, bool newLines, uint32_t tabs)
{
	for (const XML_Node& child : node.GetAllChildren())
	{
		if (child.GetChildCount() > 0)
		{
			*fs << (newLines ? getTabs(tabs) : "") << getStartNode(child) << getNewLine(newLines);

			WriteChildrenNodes(fs, child, newLines, tabs + 1);

			*fs << (newLines ? getTabs(tabs) : "") << getEndNode(child) << getNewLine(newLines);
		}
		else
		{
			*fs << (newLines ? getTabs(tabs) : "") << getStartNode(child) << child.GetValue() << getEndNode(child) << getNewLine(newLines);
		}
	}
}

void mrt::XML_Document::ReadDocumentFromStream(std::istream* inStream, XML_Document& document)
{
	std::string inputString((std::istreambuf_iterator<char>(*inStream)), std::istreambuf_iterator<char>());

	inputString.erase(std::remove_if(inputString.begin(), inputString.end(), [](char c) { return c == '\n'; }), inputString.end());

	if (inputString.empty()) return;

	size_t pos = inputString.find("?>");

	if (pos != std::string::npos)
	{
		pos += 2;

		inputString = inputString.substr(pos);
	}

	mrtInternal::XML_Tokenizer_Parser parser(&document.GetRoot(), inputString.cbegin(), inputString.cend());

	parser.Parse();
}

void mrt::XML_Document::WriteDocumentToStream(std::ostream* fs, const XML_Document& document, bool addProlog, bool newLines)
{
	if (addProlog)
	{
		*fs << getXMLprolog(document.GetVersion()) << getNewLine(newLines);
	}

	*fs << getStartNode(document.GetRoot()) << getNewLine(newLines);

	WriteChildrenNodes(fs, document.GetRoot(), newLines);

	*fs << getEndNode(document.GetRoot()) << getNewLine(newLines);
}

/***************************************/
/* MrT Global Functions Implementation */
/***************************************/

std::string mrt::getXMLprolog(const std::string& version)
{
	return "<?xml version=\"" + version + "\" encoding=\"UTF-8\"?>";
}

std::string mrt::getStartNode(const XML_Node& node)
{
	std::ostringstream ss;

	ss << "<" << node.GetName();

	for (const XML_Attribute& attribute : node.GetAllAttributes())
	{
		ss << " " << attribute.m_Name << "=\"" << attribute.m_Value << "\"";
	}

	ss << ">";

	return ss.str();
}

std::string mrt::getEndNode(const XML_Node& node)
{
	return "</" + node.GetName() + ">";
}

std::string mrt::getTabs(uint32_t amount)
{
	return std::string(amount, '\t');
}

std::string mrt::getNewLine(bool newLines)
{
	return newLines ? "\n" : "";
}

/********************************/
/* XML_Tokenizer Implementation */
/********************************/

mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer() : m_InputData(), m_Index(0) { }

mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer(std::istream* inputStream)
	: m_InputData((std::istreambuf_iterator<char>(*inputStream)), std::istreambuf_iterator<char>()), m_Index(0) { }

mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer(const std::string& inputData) : m_InputData(inputData), m_Index(0) { }

mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer(std::string::const_iterator begin, std::string::const_iterator end) : m_InputData(begin, end), m_Index(0) { }

void mrt::mrtInternal::XML_Tokenizer::SetInputData(const std::string& inputData) { m_InputData = inputData; m_Index = 0; }

mrt::mrtInternal::XML_Token mrt::mrtInternal::XML_Tokenizer::Next()
{
	if (m_Index >= m_InputData.size())
	{
		return { XML_Token_Type::END_OF_STRING, "" };
	}

	if (m_InputData[m_Index] == '<')
	{
		if (m_Index + 1 < m_InputData.size() && m_InputData[m_Index + 1] == '/')
		{
			std::string data;

			while (m_Index < m_InputData.size() && m_InputData[m_Index] != '>')
			{
				data += m_InputData[m_Index];
				m_Index++;
			}

			data += m_InputData[m_Index];
			m_Index++;

			return { XML_Token_Type::TAG_END, data };
		}
		else
		{
			std::string data;

			while (m_Index < m_InputData.size() && m_InputData[m_Index] != '>')
			{
				data += m_InputData[m_Index];
				m_Index++;
			}

			data += m_InputData[m_Index];

			if (data[data.size() - 1] == '>' && data[data.size() - 2] == '/')
			{
				m_Index++;
				return { XML_Token_Type::TAG_SELF_END, data };
			}
			else
			{
				m_Index++;
				return { XML_Token_Type::TAG_START, data };
			}
		}
	}
	else
	{
		std::string data;

		while (m_Index < m_InputData.size() && m_InputData[m_Index] != '<')
		{
			data += m_InputData[m_Index];
			m_Index++;
		}

		return { XML_Token_Type::VALUE, data };
	}
}

bool mrt::mrtInternal::XML_Tokenizer::HasNext() const { return (m_Index < m_InputData.size()) ? true : false; }

/************************************/
/* XML_Tokens_Parser Implementation */
/************************************/

mrt::mrtInternal::XML_Tokenizer_Parser::XML_Tokenizer_Parser(XML_Node* const root, std::istream* inputStream)
	: m_Root(root), m_InputData((std::istreambuf_iterator<char>(*inputStream)), std::istreambuf_iterator<char>()) { }

mrt::mrtInternal::XML_Tokenizer_Parser::XML_Tokenizer_Parser(XML_Node* const root, const std::string& inputString)
	: m_Root(root), m_InputData(inputString) { }

mrt::mrtInternal::XML_Tokenizer_Parser::XML_Tokenizer_Parser(XML_Node* const root, std::string::const_iterator begin, std::string::const_iterator end)
	: m_Root(root), m_InputData(begin, end) { }

void mrt::mrtInternal::XML_Tokenizer_Parser::Parse()
{
	XML_Tokenizer tokenizer(m_InputData.cbegin(), m_InputData.cend());

	*m_Root = ReadNode(tokenizer.Next().m_Data);

	m_CurrentEndTags.push_back(getEndNode(*m_Root));

	m_CurrentNodes.push_back(m_Root);

	while (tokenizer.HasNext())
	{
		XML_Token token = tokenizer.Next();

		switch (token.m_Type)
		{
		case XML_Token_Type::TAG_START:
		{
			m_CurrentNodes.push_back(&m_CurrentNodes.back()->AddChild(ReadNode(token.m_Data)));

			m_CurrentEndTags.push_back(getEndNode(*m_CurrentNodes.back()));

			break;
		}
		case XML_Token_Type::TAG_END:
		{
			if (token.m_Data == m_CurrentEndTags.back())
			{
				m_CurrentEndTags.pop_back();
				m_CurrentNodes.pop_back();
			}
			else
			{
				throw std::runtime_error("Invalid XML file (Missing an end tag).");
			}

			break;
		}
		case XML_Token_Type::TAG_SELF_END:
		{
			m_CurrentNodes.back()->AddChild(ReadNode(token.m_Data));

			break;
		}
		case XML_Token_Type::VALUE:
		{
			m_CurrentNodes.back()->SetValue(token.m_Data);

			break;
		}
		}
	}
}

mrt::XML_Node mrt::mrtInternal::XML_Tokenizer_Parser::ReadNode(const std::string& line)   //Reads the start node and returns a node with the name, attributes and value.
{
	XML_Node node;

	if (line.find("/>") != std::string::npos)
	{
		size_t pos = line.find(' ');

		if (pos != std::string::npos)
		{
			node.SetName(line.substr(1, pos - 1));

			ReadAttributes(line.substr(pos + 1, line.find('>') - (pos + 1) - 1), &node);
		}
		else
		{
			node.SetName(line.substr(1, line.size() - 3));
		}
	}
	else
	{
		size_t pos = line.find(' ');

		if (pos != std::string::npos)
		{
			node.SetName(line.substr(1, pos - 1));

			ReadAttributes(line.substr(pos + 1, line.size() - (pos + 2)), &node);
		}
		else
		{
			node.SetName(line.substr(1, line.size() - 2));
		}
	}

	return node;
}

void mrt::mrtInternal::XML_Tokenizer_Parser::ReadAttributes(const std::string& line, XML_Node* const node)
{
	std::string name, value, attrData;

	std::istringstream is(line);

	while (is >> attrData)
	{
		if (attrData.find('=') != std::string::npos)
		{
			name = attrData.substr(0, attrData.find('='));
			value = attrData.substr(attrData.find('=') + 2, attrData.size() - (attrData.find('=') + 2) - 1);

			node->EmplaceAttribute(name, value);
		}
	}
}
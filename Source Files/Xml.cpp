#include "../Header Files/Xml.h"

/***************************/
/* XML_Node Implementation */
/***************************/

/// <summary>
/// Initializes a new instance of the <see cref="XML_Node"/> class.
/// </summary>
mrt::XML_Node::XML_Node() : m_Name(), m_Value() { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Node"/> class.
/// </summary>
/// <param name="name"> The name of the node. </param>
/// <param name="value"> The value of the node. </param>
mrt::XML_Node::XML_Node(const std::string& name, const std::string& value) : m_Name(name), m_Value(value) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Node"/> class. From another <see cref="XML_Node"/> object.
/// </summary>
/// <param name="other"> The other <see cref="XML_Node"/> object. </param>
mrt::XML_Node::XML_Node(const XML_Node& other) : m_Name(other.m_Name), m_Value(other.m_Value), m_Attributes(other.m_Attributes), m_Children(other.m_Children) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Node"/> class. From another <see cref="XML_Node"/> object.
/// Uses move semantics to move the data from the other object to this object.
/// </summary>
/// <param name="other"> The other <see cref="XML_Node"/> object. </param>
mrt::XML_Node::XML_Node(XML_Node&& other) noexcept :
	m_Name(std::forward<std::string>(other.m_Name)),
	m_Value(std::forward<std::string>(other.m_Value)),
	m_Attributes(std::forward<std::vector<XML_Attribute>>(other.m_Attributes)),
	m_Children(std::forward<std::vector<XML_Node>>(other.m_Children)) { }

/// <summary>
/// Assigns the data from another <see cref="XML_Node"/> object to this object.
/// </summary>
/// <param name="other"> The other <see cref="XML_Node"/> object. </param>
/// <returns> A reference to this object. </returns>
mrt::XML_Node& mrt::XML_Node::operator=(const XML_Node& other)
{
	m_Name = other.m_Name;
	m_Value = other.m_Value;
	m_Attributes = other.m_Attributes;
	m_Children = other.m_Children;

	return *this;
}

/// <summary>
/// Sets the name of the xml node.
/// </summary>
/// <param name="name"> The name of the xml node. </param>
void mrt::XML_Node::SetName(std::string name) { m_Name = name; }

/// <summary>
/// Gets the name of the xml node.
/// </summary>
/// <returns> The name of the xml node. </returns>
const std::string& mrt::XML_Node::GetName() const { return m_Name; }

/// <summary>
/// Sets the value of the xml node.
/// </summary>
/// <param name="value"> The value of the xml node. </param>
void mrt::XML_Node::SetValue(std::string value) { m_Value = value; }

/// <summary>
/// Gets the value of the xml node.
/// </summary>
/// <returns> The value of the xml node. </returns>
const std::string& mrt::XML_Node::GetValue() const { return m_Value; }

/// <summary>
/// Gets the number of children of the xml node.
/// </summary>
/// <returns> The number of children of the xml node. </returns>
uint64_t mrt::XML_Node::GetChildCount() const { return m_Children.size(); }

/// <summary>
/// Gets the number of attributes of the xml node.
/// </summary>
/// <returns> The number of attributes of the xml node. </returns>
uint64_t mrt::XML_Node::GetAttributeCount() const { return m_Attributes.size(); }

/// <summary>
/// Adds an attribute to the xml node.
/// </summary>
/// <param name="name"> The name of the attribute. </param>
/// <param name="value"> The value of the attribute. </param>
mrt::XML_Node& mrt::XML_Node::AddAttribute(const std::string& name, const std::string& value)
{
	m_Attributes.emplace_back(name, value);

	return *this;
}

/// <summary>
/// Emplaces an attribute to the xml node, using move semantics.
/// </summary>
/// <typeparam name="Args"> The types of the arguments. </typeparam>
/// <param name="args"> The arguments. </param>
/// <returns> A reference to this object. </returns>
template <class... Args>
mrt::XML_Node& mrt::XML_Node::EmplaceAttribute(Args&&... args)
{
	m_Attributes.emplace_back(std::forward<Args>(args)...);

	return *this;
}

/// <summary>
/// Adds a child to the xml node.
/// </summary>
/// <param name="child"> The child to add. </param>
/// <returns> A reference to the added child. </returns>
mrt::XML_Node& mrt::XML_Node::AddChild(const XML_Node& child)
{
	m_Children.emplace_back(child);

	return m_Children.back();
}

/// <summary>
/// Emplaces a child to the xml node, using move semantics.
/// </summary>
/// <typeparam name="Args"> The types of the arguments. </typeparam>
/// <param name="args"> The arguments. </param>
/// <returns> A reference to the added child. </returns>
template <class... Args>
mrt::XML_Node& mrt::XML_Node::EmplaceChild(Args&&... args)
{
	m_Children.emplace_back(std::forward<Args>(args)...);

	return m_Children.back();
}

/// <summary>
/// Gets an attribute of the xml node by index.
/// </summary>
/// <param name="index"> The index of the attribute. </param>
/// <returns> The attribute at the specified index. </returns>
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

/// <summary>
/// Gets an attribute of the xml node by index.
/// </summary>
/// <param name="index"> The index of the attribute. </param>
/// <returns> The attribute at the specified index. </returns>
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

/// <summary>
/// Gets a child of the xml node by index.
/// </summary>
/// <param name="index"> The index of the child. </param>
/// <returns> The child at the specified index. </returns>
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

/// <summary>
/// Gets a child of the xml node by index.
/// </summary>
/// <param name="index"> The index of the child. </param>
/// <returns> The child at the specified index. </returns>
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

/// <summary>
/// Gets all the attributes of the xml node.
/// </summary>
/// <returns> A vector containing all the attributes of the xml node. </returns>
std::vector<mrt::XML_Attribute>& mrt::XML_Node::GetAllAttributes() { return m_Attributes; }

/// <summary>
/// Gets all the attributes of the xml node.
/// </summary>
/// <returns> A vector containing all the attributes of the xml node. </returns>
const std::vector<mrt::XML_Attribute>& mrt::XML_Node::GetAllAttributes() const { return m_Attributes; }

/// <summary>
/// Gets all the children of the xml node.
/// </summary>
/// <returns> A vector containing all the children of the xml node. </returns>
std::vector<mrt::XML_Node>& mrt::XML_Node::GetAllChildren() { return m_Children; }

/// <summary>
/// Gets all the children of the xml node.
/// </summary>
/// <returns> A vector containing all the children of the xml node. </returns>
const std::vector<mrt::XML_Node>& mrt::XML_Node::GetAllChildren() const { return m_Children; }

/*******************************/
/* XML_Document Implementation */
/*******************************/

/// <summary>
/// Initializes a new instance of the <see cref="XML_Document"/> class.
/// Sets the version of the xml document to "1.0".
/// </summary>
mrt::XML_Document::XML_Document() : m_Version("1.0") { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Document"/> class.
/// </summary>
/// <param version="version"> The version of the xml document. </param>
mrt::XML_Document::XML_Document(const std::string& version) :
	m_Version(version) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Document"/> class.
/// </summary>
/// <param name="root"> The root node of the xml document. </param>
/// <param name="version"> The version of the xml document. </param>
mrt::XML_Document::XML_Document(const XML_Node& root, const std::string& version) :
	m_Root(root), m_Version(version) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Document"/> class from another <see cref="XML_Document"/> object.
/// </summary>
/// <param name="other"> The other <see cref="XML_Document"/> object. </param>
mrt::XML_Document::XML_Document(const XML_Document& other) :
	m_Version(other.m_Version), m_Root(other.m_Root) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Document"/> class from another <see cref="XML_Document"/> object.
/// Uses move semantics to move the data from the other object to this object.
/// </summary>
/// <param name="other"> The other <see cref="XML_Document"/> object. </param>
mrt::XML_Document::XML_Document(XML_Document&& other) noexcept :
	m_Version(std::forward<std::string>(other.m_Version)),
	m_Root(std::forward<XML_Node>(other.m_Root)) { }

/// <summary>
/// Assigns the data from another <see cref="XML_Document"/> object to this object.
/// </summary>
/// <param name="other"> The other <see cref="XML_Document"/> object. </param>
/// <returns> A reference to this object. </returns>
mrt::XML_Document& mrt::XML_Document::operator=(const XML_Document& other)
{
	m_Version = other.m_Version;
	m_Root = other.m_Root;

	return *this;
}

/// <summary>
/// Gets the root node of the xml document.
/// </summary>
/// <returns> The root node of the xml document. </returns>
mrt::XML_Node& mrt::XML_Document::GetRoot() { return m_Root; }

/// <summary>
/// Gets the root node of the xml document.
/// </summary>
/// <returns> The root node of the xml document. </returns>
const mrt::XML_Node& mrt::XML_Document::GetRoot() const { return m_Root; }

/// <summary>
/// Gets the version of the xml document.
/// </summary>
/// <returns> The version of the xml document. </returns>
std::string& mrt::XML_Document::GetVersion() { return m_Version; }

/// <summary>
/// Gets the version of the xml document.
/// </summary>
/// <returns> The version of the xml document. </returns>
const std::string& mrt::XML_Document::GetVersion() const { return m_Version; }

/// <summary>
/// Reads an xml document from a file.
/// This function reads the xml document from the file at the specified path and stores it in the specified <see cref="XML_Document"/> object.
/// On success, it returns <see cref="XML_Document_FileError::SUCCESS"/>.
/// If any error occurs, it returns the corresponding <see cref="XML_Document_FileError"/> value.
/// </summary>
/// <param name="path"> The path of the file. </param>
/// <param name="document"> The <see cref="XML_Document"/> object to store the xml document. </param>
/// <returns> The result of the operation. </returns>
mrt::XML_Document_FileError mrt::XML_Document::ReadDocument(const std::string& path, XML_Document& document)
{
	std::ifstream fs(path, std::ios::in);

	if (!fs.is_open())
	{
		fs.close();
		return XML_Document_FileError::FAILED_TO_OPEN;
	}

	if (fs.good())
	{
		std::string inputString((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

		if (!inputString.empty())
		{
			inputString.erase(std::remove_if(inputString.begin(), inputString.end(), [](char c) { return c == '\n'; }), inputString.end());

			size_t pos = inputString.find("?>");

			if (pos != std::string::npos)
			{
				pos += 2;

				inputString = inputString.substr(pos);
			}

			mrtInternal::XML_Tokenizer_Parser parser(&document.GetRoot(), inputString.cbegin(), inputString.cend());

			parser.Parse();
		}
		else
		{
			fs.close();
			return XML_Document_FileError::FILE_EMPTY;
		}
	}
	else
	{
		fs.close();
		return XML_Document_FileError::FAILED_TO_READ;
	}

	fs.close();
	return XML_Document_FileError::SUCCESS;
}

/// <summary>
/// Writes an xml document to a file.
/// This function writes the xml document to the file at the specified path.
/// On success, it returns <see cref="XML_Document_FileError::SUCCESS"/>.
/// If any error occurs, it returns the corresponding <see cref="XML_Document_FileError"/> value.
/// </summary>
/// <param name="path"> The path of the file. </param>
/// <param name="document"> The <see cref="XML_Document"/> object to write to the file. </param>
/// <param name="addProlog"> Whether to add the xml prolog to the file. </param>
/// <param name="newLines"> Whether to add new lines to the file. </param>
/// <returns> The result of the operation. </returns>
mrt::XML_Document_FileError mrt::XML_Document::WriteDocument(const std::string& path, const XML_Document& document, bool addProlog, bool newLines)
{
	std::ofstream fs(path, std::ios::out);

	if (!fs.is_open())
	{
		return XML_Document_FileError::FAILED_TO_OPEN;
	}

	if (fs.good())
	{
		if (addProlog)
		{
			fs << getXMLprolog(document.GetVersion()) << getNewLine(newLines);
		}

		fs << getStartNode(document.GetRoot()) << getNewLine(newLines);

		WriteChildrenNodes(&fs, document.GetRoot(), newLines);

		fs << getEndNode(document.GetRoot()) << getNewLine(newLines);
	}
	else
	{
		fs.close();
		return XML_Document_FileError::FAILED_TO_WRITE;
	}

	fs.close();
	return XML_Document_FileError::SUCCESS;
}

/// <summary>
/// A recursive function to write the children nodes of an xml node to a file.
/// Will write the children nodes of the specified node to the file stream.
/// First it will write all the start nodes of all the xml nodes.
/// Then when the recursive call returns, it will write all the end nodes of all the xml nodes.
/// </summary>
/// <param name="fs"> The file stream to write to. </param>
/// <param name="node"> The xml node to write its children nodes. </param>
/// <param name="newLines"> Whether to add new lines to the file. </param>
/// <param name="tabs"> The number of tabs to add to the file. </param>
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

/// <summary>
/// Reads an xml document from a stream.
/// This function reads the xml document from the specified input stream and stores it in the specified <see cref="XML_Document"/> object.
/// DONT USE THIS FUNCTION TO READ FROM A FILE STREAM. USE <see cref="ReadDocument"/> INSTEAD.
/// </summary>
/// <param name="inStream"> The input stream to read from. </param>
/// <param name="document"> The <see cref="XML_Document"/> object to store the xml document. </param>
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

/// <summary>
/// Writes an xml document to a stream.
/// This function writes the xml document to the specified output stream.
/// DONT USE THIS FUNCTION TO WRITE TO A FILE STREAM. USE <see cref="WriteDocument"/> INSTEAD.
/// </summary>
/// <param name="fs"> The output stream to write to. </param>
/// <param name="document"> The <see cref="XML_Document"/> object to write to the output stream. </param>
/// <param name="addProlog"> Whether to add the xml prolog to the output stream. </param>
/// <param name="newLines"> Whether to add new lines to the output stream. </param>
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

/// <summary>
/// Gets the xml prolog.
/// </summary>
/// <param name="version"> The version of the xml document. </param>
/// <returns> The xml prolog. </returns>
std::string mrt::getXMLprolog(const std::string& version)
{
	return "<?xml version=\"" + version + "\" encoding=\"UTF-8\"?>";
}

/// <summary>
/// Gets the start node of an xml node.
/// </summary>
/// <param name="node"> The xml node. </param>
/// <returns> The start node of the xml node. </returns>
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

/// <summary>
/// Gets the end node of an xml node.
/// </summary>
/// <param name="node"> The xml node. </param>
/// <returns> The end node of the xml node. </returns>
std::string mrt::getEndNode(const XML_Node& node)
{
	return "</" + node.GetName() + ">";
}

/// <summary>
/// Gets the tabs. Based on the amount.
/// </summary>
/// <param name="amount"> The amount of tabs. </param>
/// <returns> The tabs. </returns>
std::string mrt::getTabs(uint32_t amount)
{
	return std::string(amount, '\t');
}

/// <summary>
/// Gets a new line. Based on the newLines parameter.
/// </summary>
/// <param name="newLines"> Whether to add new lines. </param>
/// <returns> The new line. </returns>
std::string mrt::getNewLine(bool newLines)
{
	return newLines ? "\n" : "";
}

/********************************/
/* XML_Tokenizer Implementation */
/********************************/

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer"/> class.
/// </summary>
mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer() : m_InputData(), m_Index(0) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer"/> class.
/// </summary>
/// <param name="inputStream"> The input stream to read from. </param>
mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer(std::istream* inputStream)
	: m_InputData((std::istreambuf_iterator<char>(*inputStream)), std::istreambuf_iterator<char>()), m_Index(0) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer"/> class.
/// </summary>
/// <param name="inputData"> The input data to read from. </param>
mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer(const std::string& inputData) : m_InputData(inputData), m_Index(0) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer"/> class.
/// </summary>
/// <param name="begin"> The beginning of the input data. </param>
/// <param name="end"> The end of the input data. </param>
mrt::mrtInternal::XML_Tokenizer::XML_Tokenizer(std::string::const_iterator begin, std::string::const_iterator end) : m_InputData(begin, end), m_Index(0) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer"/> class.
/// </summary>
/// <param name="inputStream"> The input stream to read from. </param>
void mrt::mrtInternal::XML_Tokenizer::SetInputData(const std::string& inputData) { m_InputData = inputData; m_Index = 0; }

/// <summary>
/// Gets the next token. From the input data.
/// The token can be a start tag, an end tag, a self ending tag or a value.
/// </summary>
/// <returns> The next token. </returns>
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

/// <summary>
/// Checks if there is a next token.
/// </summary>
/// <returns> Whether there is a next token. </returns>
bool mrt::mrtInternal::XML_Tokenizer::HasNext() const { return (m_Index < m_InputData.size()) ? true : false; }

/************************************/
/* XML_Tokens_Parser Implementation */
/************************************/

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer_Parser"/> class.
/// </summary>
/// <param name="root"> The root node of the xml document. </param>
/// <param name="inputStream"> The input stream to read from. </param>
mrt::mrtInternal::XML_Tokenizer_Parser::XML_Tokenizer_Parser(XML_Node* const root, std::istream* inputStream)
	: m_Root(root), m_InputData((std::istreambuf_iterator<char>(*inputStream)), std::istreambuf_iterator<char>()) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer_Parser"/> class.
/// </summary>
/// <param name="root"> The root node of the xml document. </param>
/// <param name="inputString"> The input string to read from. </param>
mrt::mrtInternal::XML_Tokenizer_Parser::XML_Tokenizer_Parser(XML_Node* const root, const std::string& inputString)
	: m_Root(root), m_InputData(inputString) { }

/// <summary>
/// Initializes a new instance of the <see cref="XML_Tokenizer_Parser"/> class.
/// </summary>
/// <param name="root"> The root node of the xml document. </param>
/// <param name="begin"> The beginning of the input data. </param>
/// <param name="end"> The end of the input data. </param>
mrt::mrtInternal::XML_Tokenizer_Parser::XML_Tokenizer_Parser(XML_Node* const root, std::string::const_iterator begin, std::string::const_iterator end)
	: m_Root(root), m_InputData(begin, end) { }

/// <summary>
/// Parses the input data.
/// This function parses the input data and stores the xml document in the specified root node.
/// Uses the <see cref="XML_Tokenizer"/> class to tokenize the input data.
/// Then it reads the tokens and stores the xml document in the specified root node.
/// </summary>
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

/// <summary>
/// Parses a single node from a line of data.
/// </summary>
/// <param name="line"> The line of data. </param>
/// <returns> The parsed node. </returns>
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

/// <summary>
/// Parses the attributes of a node from a line of data.
/// </summary>
/// <param name="line"> The line of data. </param>
/// <param name="node"> The node to store the attributes. </param>
void mrt::mrtInternal::XML_Tokenizer_Parser::ReadAttributes(const std::string& line, XML_Node* const node)
{
	std::string name, value, attrData;

	std::istringstream is(line);

	while (is >> attrData)
	{
		if (attrData.find('\"') != std::string::npos)
		{
			name = attrData.substr(0, attrData.find('\"') - 1);
			value = attrData.substr(attrData.find('\"') + 1, attrData.size() - (attrData.find('\"') + 1) - 1);

			node->EmplaceAttribute(name, value);
		}
	}
}
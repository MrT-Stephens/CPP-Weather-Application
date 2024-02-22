#pragma once

// XML parser for XML format.
// This is a simple XML parser that can read and write XML files.
// It can also read and write to streams.
// It is not a full XML parser and does not support all XML features.
// It is designed to be simple and easy to use.
// 
// Taken from an old project: https://github.com/MrT-Stephens/Csv-to-Desktop-Application.git

#include <deque>
#include <format>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <filesystem>

namespace mrt
{
	/*****************************/
	/* XML_Attribute Declaration */
	/*****************************/

	struct XML_Attribute
	{
		XML_Attribute() { }
		XML_Attribute(const std::string& name, const std::string& value) : m_Name(name), m_Value(value) { }

		std::string m_Name;
		std::string m_Value;
	};

	/************************/
	/* XML_Node Declaration */
	/************************/

	class XML_Node
	{
	private:
		std::string m_Name;
		std::string m_Value;
		std::vector<XML_Attribute> m_Attributes;
		std::vector<XML_Node> m_Children;
	public:
		// Constructors
		XML_Node();
		XML_Node(const std::string& name, const std::string& value = std::string());

		// Copiers & Assignments
		XML_Node(const XML_Node& other);
		XML_Node(XML_Node&& other) noexcept;
		XML_Node& operator=(const XML_Node& other);

		// Member Functions
		void SetName(std::string name);
		const std::string& GetName() const;

		void SetValue(std::string value);
		const std::string& GetValue() const;

		XML_Node& AddAttribute(const std::string& name, const std::string& value);
		template <class... Args> XML_Node& EmplaceAttribute(Args&&... args);

		XML_Node& AddChild(const XML_Node& child);
		template <class... Args> XML_Node& EmplaceChild(Args&&... args);

		XML_Attribute& GetAttribute(uint64_t index);
		const XML_Attribute& GetAttribute(uint64_t index) const;

		XML_Node& GetChild(uint64_t index);
		const XML_Node& GetChild(uint64_t index) const;

		uint64_t GetChildCount() const;
		uint64_t GetAttributeCount() const;

		std::vector<XML_Attribute>& GetAllAttributes();
		const std::vector<XML_Attribute>& GetAllAttributes() const;

		std::vector<XML_Node>& GetAllChildren();
		const std::vector<XML_Node>& GetAllChildren() const;
	};

	enum class XML_Document_FileError : uint8_t
	{
		SUCCESS = 0,
		FAILED_TO_OPEN = 1,
		FILE_EMPTY = 2
	};

	/****************************/
	/* XML_Document Declaration */
	/****************************/

	class XML_Document
	{
	private:
		std::string m_Version;
		XML_Node m_Root;
	public:
		// Constructors
		XML_Document();
		XML_Document(const std::string& version);
		XML_Document(const XML_Node& root, const std::string& version);

		// Copiers & Assignments
		XML_Document(const XML_Document& other);
		XML_Document(XML_Document&& other) noexcept;
		XML_Document& operator=(const XML_Document& other);

		// Member Functions
		XML_Node& GetRoot();
		const XML_Node& GetRoot() const;

		std::string& GetVersion();
		const std::string& GetVersion() const;

		// Functions made for reading and writing to files. USE THESE IF OUTPUTTING OR INPUTTING TO FILE.
		static XML_Document_FileError ReadDocument(const std::string& path, XML_Document& document);

		static XML_Document_FileError WriteDocument(const std::string& path, const XML_Document& document, bool addProlog = true, bool newLines = true);

		// Recursive called functions to write nodes to ouput streams.
		static void WriteChildrenNodes(std::ostream* fs, const XML_Node& node, bool newLines, uint32_t tabs = 1);

		// Universal read and write functions. USE THESE IF OUTPUTTING OR INPUTTING TO STRING STREAM, COUT, etc.
		static void ReadDocumentFromStream(std::istream* fs, XML_Document& document);

		static void WriteDocumentToStream(std::ostream* fs, const XML_Document& document, bool addProlog = true, bool newLines = true);
	};

	/************************/
	/* MrT Global Functions */
	/************************/

	static std::string getXMLprolog(const std::string& version);

	static std::string getStartNode(const XML_Node& node);

	static std::string getEndNode(const XML_Node& node);

	static std::string getTabs(uint32_t amount);

	static std::string getNewLine(bool newLines);

	namespace mrtInternal
	{
		enum class XML_Token_Type : uint8_t
		{
			TAG_START = 0,
			TAG_END = 1,
			TAG_SELF_END = 2,
			VALUE = 3,
			END_OF_STRING = 4
		};

		/*************************/
		/* XML_Token Declaration */
		/*************************/

		struct XML_Token
		{
			XML_Token_Type m_Type;
			std::string m_Data;
		};

		/*****************************/
		/* XML_Tokenizer Declaration */
		/*****************************/

		class XML_Tokenizer
		{
		private:
			// Member Variables
			std::string m_InputData;
			uint64_t m_Index;
		public:
			// Constructors
			XML_Tokenizer();
			XML_Tokenizer(std::istream* inputStream);
			XML_Tokenizer(const std::string& inputData);
			XML_Tokenizer(std::string::const_iterator begin, std::string::const_iterator end);

			// Copiers & Assignments
			XML_Tokenizer(const XML_Tokenizer& other) = delete;
			XML_Tokenizer(XML_Tokenizer&& other) noexcept = delete;
			XML_Tokenizer& operator=(const XML_Tokenizer& other) = delete;

			// Member Functions
			void SetInputData(const std::string& inputData);

			XML_Token Next();

			bool HasNext() const;
		};

		/*********************************/
		/* XML_Tokens_Parser Declaration */
		/*********************************/

		class XML_Tokenizer_Parser
		{
		private:
			// Member Variables
			std::string m_InputData;
			XML_Node* m_Root;
			std::deque<std::string> m_CurrentEndTags;
			std::deque<XML_Node*> m_CurrentNodes;
		public:
			// Constructors
			XML_Tokenizer_Parser(XML_Node* const root, std::istream* inputStream);
			XML_Tokenizer_Parser(XML_Node* const root, const std::string& inputString);
			XML_Tokenizer_Parser(XML_Node* const root, std::string::const_iterator begin, std::string::const_iterator end);

			// Copiers & Assignments
			XML_Tokenizer_Parser(const XML_Tokenizer_Parser& other) = delete;
			XML_Tokenizer_Parser(XML_Tokenizer_Parser&& other) noexcept = delete;
			XML_Tokenizer_Parser& operator=(const XML_Tokenizer_Parser& other) = delete;

			// Member Functions
			void Parse();

			// Static Functions
			static XML_Node ReadNode(const std::string& line);

			static void ReadAttributes(const std::string& line, XML_Node* const node);
		};
	}
}
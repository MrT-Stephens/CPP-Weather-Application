#pragma once

#include "../Header Files/ProofID.h"
#include "../Header Files/NoCopy.h"

#include <string>
#include <vector>

class Subject
{
private:
	std::string m_Email;
	std::string m_FirstName;
	std::string m_LastName;
	ProofID m_ProofID;
public:
	Subject() { }
	Subject(const std::string& email, const std::string& first_name, const std::string& last_name)
		: m_Email(email), m_FirstName(first_name), m_LastName(last_name) { }

	Subject(const std::string& email, const std::string& first_name, const std::string& last_name, const ProofID& proof_id)
		: m_Email(email), m_FirstName(first_name), m_LastName(last_name), m_ProofID(proof_id) { }

	~Subject() { m_Email = ""; m_FirstName = ""; m_LastName = ""; }

	std::string GetEmail() const { return m_Email; }
	std::string GetFirstName() const { return m_FirstName; }
	std::string GetLastName() const { return m_LastName; }
	std::string GetFullName() const { return m_FirstName + " " + m_LastName; }

	friend void operator>>(const Subject& subject, std::vector<std::string>& vec)
	{
		vec.push_back(subject.m_Email);
		vec.push_back(subject.m_FirstName);
		vec.push_back(subject.m_LastName);
	}
};
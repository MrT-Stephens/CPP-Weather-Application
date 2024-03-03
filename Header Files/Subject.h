#pragma once

#include "../Header Files/ProofID.h"
#include "../Header Files/NoCopy.h"

#include <string>
#include <vector>

/// <summary>
/// A class that represents a subject.
/// A subject is a person who is being identified.
/// A subject has an email, first name, last name, and a proof id.
/// </summary>
class Subject
{
private:
	std::string m_Email;
	std::string m_FirstName;
	std::string m_LastName;
	ProofID m_ProofID;
public:
	/// <summary>
	/// Initializes a empty instance of the <see cref="Subject"/> class.
	/// </summary>
	Subject() { }

	/// <summary>
	/// Initializes a new instance of the <see cref="Subject"/> class.
	/// </summary>
	/// <param name="email"> The email of the user. </param>
	/// <param name="first_name"> The first name of the user. </param>
	/// <param name="last_name"> The last name of the user. </param>
	Subject(const std::string& email, const std::string& first_name, const std::string& last_name)
		: m_Email(email), m_FirstName(first_name), m_LastName(last_name) { }

	/// <summary>
	/// Initializes a new instance of the <see cref="Subject"/> class.
	/// </summary>
	/// <param name="email"> The email of the user. </param>
	/// <param name="first_name"> The first name of the user. </param>
	/// <param name="last_name"> The last name of the user. </param>
	/// <param name="proof_id"> The proof id of the user. </param>
	Subject(const std::string& email, const std::string& first_name, const std::string& last_name, const ProofID& proof_id)
		: m_Email(email), m_FirstName(first_name), m_LastName(last_name), m_ProofID(proof_id) { }

	/// <summary>
	/// Destroys the instance of the <see cref="Subject"/> class.
	/// For added security, the email, first name, and last name are set to empty strings.
	/// </summary>
	~Subject() { m_Email = ""; m_FirstName = ""; m_LastName = ""; }

	// Getters
	std::string GetEmail() const { return m_Email; }
	std::string GetFirstName() const { return m_FirstName; }
	std::string GetLastName() const { return m_LastName; }
	std::string GetFullName() const { return m_FirstName + " " + m_LastName; }
	ProofID GetProofID() const { return m_ProofID; }

	/// <summary>
	/// Checks if the subject is empty.
	/// </summary>
	/// <returns> True if the subject is empty, otherwise false. </returns>
	bool IsEmpty() const { return (m_Email.empty() && m_FirstName.empty() && m_LastName.empty() && m_ProofID == ProofID()); }

	/// <summary>
	/// Checks if two subjects are equal.
	/// </summary>
	/// <param name="subject"> The subject to compare to. </param>
	/// <returns> True if the subjects are equal, otherwise false. </returns>
	bool operator==(const Subject& subject) const
	{
		return (m_Email == subject.m_Email && m_FirstName == subject.m_FirstName && m_LastName == subject.m_LastName && m_ProofID == subject.m_ProofID);
	}

	/// <summary>
	/// Uses the >> operator to add the subject's email, first name, and last name to a vector.
	/// </summary>
	/// <param name="subject"> The subject to add to the vector. </param>
	/// <param name="vec"> The vector to add the subject to. </param>
	friend void operator>>(const Subject& subject, std::vector<std::string>& vec)
	{
		vec.push_back(subject.m_Email);
		vec.push_back(subject.m_FirstName);
		vec.push_back(subject.m_LastName);
	}
};
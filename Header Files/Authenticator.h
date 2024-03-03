#pragma once

#include "../Header Files/Subject.h"
#include "../Header Files/ProofID.h"
#include "../Header Files/AuthenticatorInfo.h"
#include "../Header Files/SubjectInfo.h"
#include "../Header Files/NoCopy.h"

#include <string>

/// <summary>
/// The authenticator class is used to authenticate a user and to register a user.
/// It also allows for re-authentication of a user.
/// </summary>
class Authenticator : private NoCopy
{
private:
	SubjectInfo m_SubjectInfo;
public:
	Authenticator()
	{
		std::srand(std::time(nullptr));
	}

	/// <summary>
	/// Authenticates a user with the given email and password.
	/// </summary>
	/// <param name="email"> The email of the user. </param>
	/// <param name="password"> The password of the user. </param>
	/// <returns> A pair of a boolean and a subject. The boolean is true if the user was authenticated and false if the user was not authenticated. The subject is the user that was authenticated. </returns>
	std::pair<bool, Subject> Authenticate(const std::string& email, const std::string& password)
	{
		AuthenticatorInfo info;

		if (info.ValidateSubject(email, password))
		{
			std::hash<std::string> hash;
			ProofID proof(std::to_string(hash._Do_hash(email + std::to_string(rand() % 1000))));

			Subject temp = m_SubjectInfo.Get(email);

			temp = Subject(email, temp.GetFirstName(), temp.GetLastName(), proof);
			m_SubjectInfo.Add(email, temp.GetFirstName(), temp.GetLastName(), proof);

			return std::make_pair(true, temp);
		}
		else
		{
			return std::make_pair(false, Subject());
		}
	}

	/// <summary>
	/// Registers a user with the given email, first name, last name, and password.
	/// </summary>
	/// <param name="email"> The email of the user. </param>
	/// <param name="first_name"> The first name of the user. </param>
	/// <param name="last_name"> The last name of the user. </param>
	/// <param name="password"> The password of the user. </param>
	void Register(const std::string& email, const std::string& first_name, const std::string& last_name, const std::string& password)
	{
		AuthenticatorInfo info;

		info.AddSubject(email, password);

		m_SubjectInfo.Add(email, first_name, last_name, ProofID());
	}

	/// <summary>
	/// Re-authenticates a user with the given subject.
	/// Uses the subjects ProofID to re-authenticate the user.
	/// Will regenerate the ProofID for the user, if the user is re-authenticated.
	/// </summary>
	/// <param name="subject"> The subject to re-authenticate. </param>
	/// <returns> A pair of a boolean and a subject. The boolean is true if the user was re-authenticated and false if the user was not re-authenticated. The subject is the user that was re-authenticated. </returns>
	std::pair<bool, Subject> ReAuthenticate(const Subject& subject)
	{
		Subject temp = m_SubjectInfo.Get(subject.GetEmail());

		if (temp == subject)
		{
			std::hash<std::string> hash;
			ProofID proof(std::to_string(hash._Do_hash(subject.GetEmail() + std::to_string(rand() % 1000))));

			temp = Subject(subject.GetEmail(), subject.GetFirstName(), subject.GetLastName(), proof);

			m_SubjectInfo.Add(subject.GetEmail(), subject.GetFirstName(), subject.GetLastName(), proof);

			return std::make_pair(true, temp);
		}
		else
		{
			return std::make_pair(false, Subject());
		}
	}

	/// <summary>
	/// Gets all the subjects that are registered from the 'SubjectInfo' class.
	/// </summary>
	const std::vector<Subject>& GetSubjects() const
	{
		return m_SubjectInfo.GetAllSubjects();
	}
};
#pragma once

#include "../Header Files/Subject.h"
#include "../Header Files/ProofID.h"
#include "../Header Files/AuthenticatorInfo.h"
#include "../Header Files/SubjectInfo.h"
#include "../Header Files/NoCopy.h"

#include <string>

class Authenticator : private NoCopy
{
private:
	SubjectInfo m_SubjectInfo;
public:
	Authenticator()
	{
		std::srand(std::time(nullptr));
	}

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

	void Register(const std::string& email, const std::string& first_name, const std::string& last_name, const std::string& password)
	{
		AuthenticatorInfo info;

		info.AddSubject(email, password);

		m_SubjectInfo.Add(email, first_name, last_name, ProofID());
	}

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

	const std::vector<Subject>& GetSubjects() const
	{
		return m_SubjectInfo.GetAllSubjects();
	}
};
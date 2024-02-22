#pragma once

#include "../Header Files/Subject.h"
#include "../Header Files/Storage.h"
#include "../Header Files/NoCopy.h"

#include <vector>

class SubjectInfo : private NoCopy
{
private:
	std::vector<Subject> m_Subjects;

	std::vector<Subject>::iterator GetSubject(const std::string& email)
	{
		return std::find_if(m_Subjects.begin(), m_Subjects.end(), [&email](Subject& subject)
			{
				return subject.GetEmail() == email;
			});
	}
public:
	SubjectInfo()
	{
		if (!Storage::Read(std::to_string(typeid(this).hash_code()), m_Subjects))
		{
			m_Subjects.emplace_back("admin@admin.com", "Admin", "Admin");
		}
	}

	~SubjectInfo()
	{
		Storage::Write(std::to_string(typeid(this).hash_code()), m_Subjects);

		m_Subjects.clear();
	}

	void Add(const std::string& email, const std::string& first_name, const std::string& last_name, const ProofID& proofid)
	{
		std::vector<Subject>::iterator it = GetSubject(email);

		if (GetSubject(email) == m_Subjects.end())
		{
			m_Subjects.emplace_back(email, first_name, last_name, proofid);
		}
		else
		{
			*it = Subject(email, first_name, last_name, proofid);
		}
	}

	Subject Get(const std::string& email)
	{
		return *GetSubject(email);
	}
};
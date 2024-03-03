#pragma once

#include "../Header Files/Subject.h"
#include "../Header Files/Storage.h"
#include "../Header Files/NoCopy.h"

#include <vector>

/// <summary>
/// This class is responsible for managing the subjects.
/// It stores the subjects in a vector and provides methods to add, get and list all subjects.
/// </summary>
class SubjectInfo : private NoCopy
{
private:
	std::vector<Subject> m_Subjects;

	/// <summary>
	/// This method returns an iterator to the subject with the given email.
	/// </summary>
	/// <param name="email"> The email of the user. </param>
	/// <returns> An iterator to the subject with the given email. </returns>
	std::vector<Subject>::iterator GetSubject(const std::string& email)
	{
		return std::find_if(m_Subjects.begin(), m_Subjects.end(), [&email](Subject& subject)
			{
				return subject.GetEmail() == email;
			});
	}
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SubjectInfo"/> class.
	/// It reads the subjects from the storage and stores them in the vector.
	/// If the storage is empty, it adds the admin as the first subject.
	/// </summary>
	SubjectInfo()
	{
		if (!Storage::Read(std::to_string(typeid(this).hash_code()), m_Subjects))
		{
			m_Subjects.emplace_back("admin@admin.com", "Admin", "Admin");
		}
	}

	/// <summary>
	/// Destroys the instance of the <see cref="SubjectInfo"/> class.
	/// It writes the subjects to the storage.
	/// </summary>
	~SubjectInfo()
	{
		Storage::Write(std::to_string(typeid(this).hash_code()), m_Subjects);

		m_Subjects.clear();
	}

	/// <summary>
	/// Adds a new subject to the vector of subjects.
	/// </summary>
	/// <param name="email"> The email of the user. </param>
	/// <param name="first_name"> The first name of the user. </param>
	/// <param name="last_name"> The last name of the user. </param>
	/// <param name="proofid"> The proof id of the user. </param>
	void Add(const std::string& email, const std::string& first_name, const std::string& last_name, const ProofID& proofid)
	{
		std::vector<Subject>::iterator it = GetSubject(email);

		Subject subject(email, first_name, last_name, proofid);

		if (GetSubject(email) == m_Subjects.end())
		{
			m_Subjects.push_back(subject);
		}
		else
		{
			*it = subject;
		}
	}

	/// <summary>
	/// Gets the subject with the given email.
	/// Calls the GetSubject method and returns the subject.
	/// </summary>
	/// <param name="email"> The email of the user. </param>
	/// <returns> The subject with the given email. </returns>
	Subject Get(const std::string& email)
	{
		return *GetSubject(email);
	}

	const std::vector<Subject>& GetAllSubjects() const
	{
		return m_Subjects;
	}
};
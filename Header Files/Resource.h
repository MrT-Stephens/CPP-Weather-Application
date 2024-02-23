#pragma once

#include "../Header Files/NoCopy.h"
#include "../Header Files/Subject.h"
#include "../Header Files/Permission.h"

#include <any>

class Resource : private NoCopy
{
private:
	Permission m_Permission;
public:
	Resource()
	{

	}

	std::pair<bool, std::any> AccessResource(const Subject& subject, uint32_t resource_id = 0, AccessType access_type = AccessType::NO_ACCESS)
	{
		uint8_t user_permission = m_Permission.CheckPermission(subject.GetEmail(), resource_id);

		switch (resource_id)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		}
	}
};
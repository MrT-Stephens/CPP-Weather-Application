#pragma once

#include "../Header Files/NoCopy.h"
#include "../Header Files/Subject.h"
#include "../Header Files/Permission.h"

class Resource : private NoCopy
{
public:
	Resource(const Subject& subject, Permission& permission, uint32_t resource_id = 0, AccessType access_type = AccessType::NO_ACCESS);


};
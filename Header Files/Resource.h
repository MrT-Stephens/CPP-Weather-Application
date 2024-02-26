#pragma once

#include "../Header Files/NoCopy.h"
#include "../Header Files/Subject.h"
#include "../Header Files/Permission.h"

#include <elements.hpp>

template <typename... Types>
class Resource : private NoCopy
{
private:
	Permission<Types...> m_Permission;
public:
	Resource()
	{

	}

	template<typename View>
	std::shared_ptr<View> AccessResource(std::shared_ptr<cycfi::elements::view> main_view, const Subject& subject, uint32_t resource_id = 0)
	{
		uint8_t user_permission = (uint8_t)m_Permission.CheckPermission(subject.GetEmail(), resource_id);

		return std::make_shared<View>(main_view, user_permission);
	}

	const std::unordered_map<std::string, typename Permission<Types...>::Resources>& GetResourceAccesses() const
	{
		return m_Permission.GetResourceAccesses();
	}
};
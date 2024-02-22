#pragma once

#include "../Header Files/NoCopy.h"

#include <elements.hpp>

class View : private NoCopy
{
protected:
	cycfi::artist::color m_BackgroundColor;
	std::shared_ptr<cycfi::elements::view> m_MainView;
public:
	View(std::shared_ptr<cycfi::elements::view> main_view);

	virtual void InitView() = 0;

	virtual void UpdateView() = 0;
};
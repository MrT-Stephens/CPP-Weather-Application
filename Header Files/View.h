#pragma once

#include <elements.hpp>

class View : public cycfi::elements::view
{
protected:
	cycfi::artist::color m_BackgroundColor;
public:
	View(std::shared_ptr<cycfi::elements::window> window);

	virtual void InitView() = 0;

	virtual void UpdateView() = 0;
};
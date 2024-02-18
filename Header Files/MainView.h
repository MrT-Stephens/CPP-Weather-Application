#pragma once

#include "../Header Files/View.h"

class MainView : public View
{
private:
	cycfi::elements::rbox_element m_RoundedBox{ cycfi::elements::rbox(m_BackgroundColor.level(1.5f)) };
public:
	MainView(std::shared_ptr<cycfi::elements::window> window);

	void InitView() override;

	void UpdateView() override;
};
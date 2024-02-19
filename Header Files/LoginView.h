#pragma once

#include "../Header Files/View.h"

class LoginView : public View
{
public:
	LoginView(std::shared_ptr<cycfi::elements::window> window);

	void InitView() override;

	void UpdateView() override;

	void SetLoginCallback(std::function<void(bool)> callback);
};
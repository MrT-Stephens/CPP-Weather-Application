#include "../Header Files/View.h"

View::View(std::shared_ptr<cycfi::elements::window> window)
	: cycfi::elements::view(*window)
{
	m_BackgroundColor = cycfi::artist::rgba(35, 35, 37, 255);
}
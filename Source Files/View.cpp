#include "../Header Files/View.h"

View::View(std::shared_ptr<cycfi::elements::view> main_view)
	: m_MainView(main_view)
{
	m_BackgroundColor = cycfi::artist::rgba(35, 35, 37, 255);
}
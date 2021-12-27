#include "Drawer.h"

void DrawerImpl::OnFrameStarted()
{
	_renderWindow->clear(sf::Color(77, 83, 140));
}

void DrawerImpl::Add(sf::Drawable& drawable)
{
	_renderWindow->draw(drawable);
}

void DrawerImpl::OnFrameEnded()
{
	_renderWindow->display();
}

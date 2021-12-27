#pragma once

#include "Singleton.h"
#include "SFML/Graphics.hpp"


class DrawerImpl
{
	sf::RenderWindow* _renderWindow;
public:
	void SetWindow(sf::RenderWindow* renderWindow) { _renderWindow = renderWindow; }
	void OnFrameStarted();
	void Add(sf::Drawable& drawable);
	void OnFrameEnded();
};

typedef Singletons<DrawerImpl> DrawerSingleton;
#define Drawer (DrawerSingleton::ref())
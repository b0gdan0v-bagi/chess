#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Singleton.h"
#include "field.h"


class Engine
{
	sf::RenderWindow window;
	sf::Vector2f mResolution;
	Field* mField;

	sf::Image _image;

	void OnStarted();
	void OnRestarted();
	void SetWindow();
	void Draw();
	void Update(const float dt);

public:
	Engine();
	~Engine();

	int Start();


};


typedef Singletons<Engine> EngineSingleton;
#define GameEngine (EngineSingleton::ref())

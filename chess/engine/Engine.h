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
	float _timeDiv;

	sf::Image _image;
	sf::Clock _clock;

	void OnStarted();
	void OnRestarted();
	void OnEnded();

	void SetWindow();
	void Draw();
	void Input();
	void Update();

public:
	Engine();
	~Engine();

	void Start();


};


typedef Singletons<Engine> EngineSingleton;
#define GameEngine (EngineSingleton::ref())

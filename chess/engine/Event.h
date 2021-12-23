#pragma once

#include <unordered_map>
#include <algorithm>
#include "Singleton.h"
#include "SFML/Graphics.hpp"

class GameEventBase;

class Listener
{
public:
	virtual void TakeEvent(GameEventBase* event) = 0;
};

enum class eEventType
{
	MouseMoved,
	MouseClicked
};

class GameEventBase
{
protected:
	eEventType mType;
public:
	eEventType GetType() {
		return mType;
	}
};

class GameEventMouseMoved : public GameEventBase
{
	sf::Vector2i mMousePos;
public:
	GameEventMouseMoved(sf::Vector2i mousePos);
	sf::Vector2i GetMousePos() { return mMousePos; }
};

class GameEventMouseClicked : public GameEventBase
{
	sf::Vector2i mMousePos;
public:
	GameEventMouseClicked(sf::Vector2i mousePos);
	sf::Vector2i GetMousePos() { return mMousePos; }
};

class EventManagerImpl
{
	sf::Window* mWindow = nullptr;
	std::vector<Listener*> mListeners;
public:
	void SetWindow(sf::Window* window) { mWindow = window; }
	void HandleSFMLEvents();
	void RegisterListener(Listener* listener) { mListeners.push_back(listener); }
	void PostEvent(GameEventBase* event);
};


typedef Singletons<EventManagerImpl> EventManagerSingleton;
#define EventManager (EventManagerSingleton::ref())

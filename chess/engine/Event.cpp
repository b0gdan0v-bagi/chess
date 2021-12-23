#include "Event.h"

void EventManagerImpl::HandleSFMLEvents()
{
	sf::Event event;
	while (mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow->close();
			return;
		}
		GameEventBase* ev = nullptr;
		if (event.type == sf::Event::MouseMoved)
		{   
			ev = new GameEventMouseMoved(sf::Mouse::getPosition(*mWindow));
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			ev = new GameEventMouseClicked(sf::Mouse::getPosition(*mWindow));
		}
		if (ev)
		{
			PostEvent(ev);
			delete ev;
		}
	}
}

void EventManagerImpl::PostEvent(GameEventBase* event)
{
	for (auto& listener : mListeners)
	{
		listener->TakeEvent(event);
	}
}

GameEventMouseMoved::GameEventMouseMoved(sf::Vector2i mousePos) : GameEventBase(), mMousePos(mousePos)
{
	mType = eEventType::MouseMoved;
}

GameEventMouseClicked::GameEventMouseClicked(sf::Vector2i mousePos) : GameEventBase(), mMousePos(mousePos)
{
	mType = eEventType::MouseClicked;
}

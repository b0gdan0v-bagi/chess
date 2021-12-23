#include "figure.h"

void Figure::DrawSelf()
{
	_window->draw(mSprite);
}

Figure::Figure(sf::RenderWindow* window, ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos)
	: Entity("figure", window)
	, mPlayerColor(color)
	, mPos(pos)
	, mCell(nullptr)
{
	SetSize(size);
}

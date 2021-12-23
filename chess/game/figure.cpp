#include "figure.h"
#include "cell.h"

void Figure::DrawSelf()
{
	_window->draw(mSprite);
}

void Figure::UpdateSelf(const float dt)
{
	mSprite.setPosition(mCell->GetPosition());
}

Figure::Figure(sf::RenderWindow* window, ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos)
	: Entity("figure", window)
	, mPlayerColor(color)
	, mPos(pos)
	, mCell(nullptr)
{
	SetSize(size);
}

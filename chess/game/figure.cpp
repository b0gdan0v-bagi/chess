#include "figure.h"
#include "cell.h"

void Figure::DrawSelf()
{
	Drawer->Add(mSprite);
}

void Figure::UpdateSelf(const float dt)
{
	mSprite.setPosition(mCell->GetPosition());
}

Figure::Figure(ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos)
	: Entity("figure")
	, mPlayerColor(color)
	, mPos(pos)
	, mCell(nullptr)
	, mFigureType(eFigureType::Count)
{
	SetSize(size);
}

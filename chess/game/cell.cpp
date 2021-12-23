#include "cell.h"

void Cell::DrawSelf()
{
	auto shape = sf::RectangleShape(_size);
	shape.setPosition(GetPosition());
	shape.setFillColor(mColor);
	_window->draw(shape);
}

void Cell::UpdateSelf(const float dt)
{

}

Cell::Cell(const Field* field, sf::RenderWindow* window, const sf::Vector2f size, const sf::Vector2i coord) 
	: Entity("cell",window)
	, mField(field)
	, mCoord(coord)
	, mFigure(nullptr)
{
	_size = size;
	
}

void Cell::SetFigure(Figure* figure)
{
	ClearChidren();
	AddChild(figure);
	figure->SetCell(this);
	mFigure = figure;
}

void Cell::UnsetFigure()
{
	ClearChidren();
	mFigure = nullptr;
}

bool Cell::HasFigure()
{
	return mFigure != nullptr;
}

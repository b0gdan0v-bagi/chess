#include "cell.h"

void Cell::DrawSelf()
{
	auto shape = sf::RectangleShape(_size);
	shape.setPosition(GetPosition());
	shape.setFillColor(mSelected ? sf::Color::Red : mColor);
	Drawer->Add(shape);
}

void Cell::UpdateSelf(const float dt)
{

}

Cell::Cell(Field* field, const sf::Vector2f size, const sf::Vector2i coord) 
	: Entity("cell")
	, mField(field)
	, mCoord(coord)
	, mFigure(nullptr)
	, mSelected(false)
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

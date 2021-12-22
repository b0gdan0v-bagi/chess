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
	_sprite.setPosition(GetPosition());
}

Cell::Cell(const Field* field, sf::RenderWindow* window, const sf::Vector2f size, const sf::Vector2i coord) 
	: Entity("cell",window)
	, mField(field)
	, mCoord(coord)
{
	_size = size;
	
}

#include "field.h"
#include "Resourse.h"

void Field::DrawSelf()
{
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color(150, 50, 250));
	_window->draw(shape);
	if (auto item = ResourseManager->GetData<ItemTexture>("chess"))
	{
		_window->draw(item->GetSprite());
	}
}

Field::Field(sf::RenderWindow* window, const sf::Vector2f resolution): Entity("field", window)
{
	SetTopOwner();
	mCellsData.resize(mFieldSize * mFieldSize, nullptr);
	mCellSize = sf::Vector2f(static_cast<float>(resolution.x / mFieldSize), static_cast<float>(resolution.y / mFieldSize));
	bool black = false;
	for (size_t y = 0; y < mFieldSize; y++)
	{
		for (size_t x = 0; x < mFieldSize; x++) 
		{
			Cell* cell = new Cell(this, _window, mCellSize, sf::Vector2i(x,y));
			cell->SetColor(black ? sf::Color::Black : sf::Color::White);
			mCellsData[x + y * mFieldSize] = cell;
			cell->SetPosition(sf::Vector2f(x*mCellSize.x,y*mCellSize.y));
			AddChild(cell);
			black = !black;
		}
	}
}


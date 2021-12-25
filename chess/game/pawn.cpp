#include "pawn.h"
#include "Resourse.h"
#include "Utils.h"
#include "field.h"

Pawn::Pawn(sf::RenderWindow* window, ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos)
	:Figure(window, color, size, pos)
{
	auto getData = color == ePlayerColor::White ? "white_pawn" : "black_pawn";
	mSprite = ResourseManager->GetData<ItemTexture>(getData)->GetSprite();

	sf::Vector2f v = { mSprite.getLocalBounds().width, mSprite.getLocalBounds().height };
	auto scale = sf::Vector2f(size.x / v.x, size.y / v.y);
	mSprite.setScale(scale);
	mSprite.setPosition(pos);
}

std::vector<Cell*> Pawn::GetPossibleCells()
{
	std::vector<Cell*> res;
	if (auto cell = GetCell())
	{
		res = cell->GetField()->GetFreeCells(cell);
	}
	return res;
}

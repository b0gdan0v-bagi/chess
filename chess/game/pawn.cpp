#include "pawn.h"
#include "Resourse.h"
#include "Utils.h"
#include "field.h"

Pawn::Pawn(ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos)
	:Figure(color, size, pos)
{
	mFigureType = eFigureType::Pawn;

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

Cell* Pawn::GetPossibleCellWithDirection(eDirection direction)
{
	auto cell = GetCell();
	if (!cell)
		return nullptr;
	auto subCell = cell->GetField()->GetCell(cell, direction);
	if (!subCell)
		return nullptr;
	return subCell->HasFigure() ? nullptr : subCell;
}

std::vector<eDirection> Pawn::GetPossibleDirections()
{
	std::vector<eDirection> res;
	for (size_t i = 0, n = static_cast<size_t>(eDirection::Count); i < n; i++)
	{
		if (auto cell = GetPossibleCellWithDirection(static_cast<eDirection>(i)))
		{
			res.push_back(static_cast<eDirection>(i));
		}
	}
	return res;
}

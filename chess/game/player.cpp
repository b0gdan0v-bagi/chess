#include "player.h"

Cell* Player::ClickedAvaliableCell(Cell* cell)
{
	if (!mSelectedCell || !cell)
		return nullptr;
	for (auto& subCell : mPotentialCells)
	{
		if (cell == subCell)
			return cell;
	}
	return nullptr;
}

Player::Player(Field* field, ePlayerColor color, PlayerController* playerController)
	:mField(field), mPlayerColor(color), mIsReadyToMove(false), mPlayerController(playerController)
{
}

Human::Human(Field* field, ePlayerColor color, PlayerController* playerController) :Player(field, color, playerController)
{
}

void Human::MakeMove(Cell* cell)
{
	if (!IsReadyToMove())
	{
		if (auto figure = cell->GetFigure())
		{
				if (figure->GetPlayerColor() == GetPlayerColor())
				{
					mField->UnselectCells();
					mPotentialCells = figure->GetPossibleCells();
					if (!mPotentialCells.empty())
					{
						for (auto& marked : mPotentialCells)
						{
							marked->SetSelected(true);
						}
						mSelectedCell = cell;
						SetIsReadyToMove(true);
					}
			}
		}
	}
	else
	{
		if (auto figure = mSelectedCell->GetFigure())
		{
			if (auto subCell = ClickedAvaliableCell(cell))
			{
				subCell->SetFigure(figure);
				mSelectedCell->UnsetFigure();
				SetIsReadyToMove(false);
				mField->UnselectCells();
				mPlayerController->OnMoveEnded();
			}
		}
	}
}

Computer::Computer(Field* field, ePlayerColor color, PlayerController* playerController) : Player(field, color, playerController)
{
}

#include "player.h"
#include "Resourse.h"
#include "Logger.h"
#include <algorithm>
#include <random>
#include "pawn.h"


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

void Player::CompleteMove(Figure* figure, Cell* cell)
{
	cell->SetFigure(figure);
	mSelectedCell->UnsetFigure();
	SetIsReadyToMove(false);
	mField->UnselectCells();
	mPlayerController->OnMoveEnded();
	mField->CheckWinCondition(GetPlayerColor());
	
	std::string playerColor = GetPlayerColor() == ePlayerColor::Black ? "Black" : "White";
	auto coords = cell->GetCoord();
	LoggerManager->logFull(playerColor + " completed his move " + std::to_string(coords.x) + " " + std::to_string(coords.y));
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
				CompleteMove(figure, subCell);
			}
			else
			{
				SetIsReadyToMove(false);
				MakeMove(cell);
			}
		}
	}
}

Computer::Computer(Field* field, ePlayerColor color, PlayerController* playerController)
	: Player(field, color, playerController)
	, mStrategy(eStrategy::Random)
	, mCounter(0)
	, mCounter_2(0)
{
	auto data = ResourseManager->GetData<ItemData>("field");
	std::string type = color == ePlayerColor::Black ? "black" : "white";
	auto strategy = data->GetData("strategy_" + type);
	if (strategy == "random")
	{
		mStrategy = eStrategy::Random;
	}
	else if (strategy == "allForward")
	{
		mStrategy = eStrategy::AllForward;
	}
	else
	{
		LoggerManager->logFull("problem with reading strategy, set to random");
	}
}

void Computer::MakeMove(Cell* cell)
{
	mControlledCells = mField->GetOccupiedCells(GetPlayerColor()); // TODO not optiml
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	switch (mStrategy)
	{
	case Computer::eStrategy::Random:
	{
		std::shuffle(std::begin(mControlledCells), std::end(mControlledCells), e);
		for (auto& subCell : mControlledCells)
		{
			if (auto figure = subCell->GetFigure())
			{
				auto possibleFigureMoves = figure->GetPossibleCells();
				if (!possibleFigureMoves.empty())
				{
					std::shuffle(std::begin(possibleFigureMoves), std::end(possibleFigureMoves), e);
					mSelectedCell = subCell;
					CompleteMove(figure, possibleFigureMoves.front());
					return;
				}
			}
		}
	}
	break;
	case Computer::eStrategy::AllForward:
	{
		std::vector<eDirection> directionsStrategy;
		if (GetPlayerColor() == ePlayerColor::White)
		{
			directionsStrategy = {eDirection::Top, eDirection::Left, eDirection::Bottom, eDirection::Right};
			std::sort(mControlledCells.begin(), mControlledCells.end(),
				[](Cell* a, Cell* b) -> bool
				{
					return a->GetCoord().x > b->GetCoord().x;
				});
		}
		else
		{
			directionsStrategy = { eDirection::Bottom, eDirection::Right, eDirection::Top, eDirection::Right };
			std::sort(mControlledCells.begin(), mControlledCells.end(),
				[](Cell* a, Cell* b) -> bool
				{
					return a->GetCoord().x < b->GetCoord().x;
				});
		}
		
		// hint for AI :D
		if (mCounter_2 > Utils::Random(4, 6))
		{
			mCounter_2 = 0;
			if (GetPlayerColor() == ePlayerColor::White)
			{
				directionsStrategy = { eDirection::Left, eDirection::Bottom, eDirection::Right, eDirection::Top };
			}
			else
			{
				directionsStrategy = { eDirection::Right, eDirection::Top, eDirection::Left, eDirection::Bottom };
			}
		}
		else {
			if (mCounter >= Utils::Random(3, 9) /*&& mCounter % 2 == 0*/)
			{
				mCounter = 0;
				if (GetPlayerColor() == ePlayerColor::White)
				{
					directionsStrategy = { eDirection::Left, eDirection::Bottom, eDirection::Right, eDirection::Top };
				}
				else
				{
					directionsStrategy = { eDirection::Right, eDirection::Top, eDirection::Left, eDirection::Bottom };
				}
			}
		}
		for (auto& dir : directionsStrategy)
		{
			for (auto& subCell : mControlledCells)
			{
				if (auto figure = subCell->GetFigure())
				{
					if (figure->GetFigureType() == eFigureType::Pawn)
					{
						auto pawn = static_cast<Pawn*>(figure);
						if (auto possibleCell = pawn->GetPossibleCellWithDirection(dir))
						{
							mSelectedCell = subCell;
							CompleteMove(figure, possibleCell);
							mCounter++;
							mCounter_2++;
							return;
						}
					}
				}
			}
		}
	}
	break;
	}
	LoggerManager->logFull("problem with making move for computer");
}


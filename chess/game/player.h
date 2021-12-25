#pragma once
#include "Utils.h"
#include "field.h"

class PlayerController;

class Player
{
protected:
	ePlayerColor mPlayerColor;
	Field* mField;
	bool mIsReadyToMove;

	std::vector<Cell*> mPotentialCells;
	Cell* mSelectedCell;
	PlayerController* mPlayerController;

	Cell* ClickedAvaliableCell(Cell* cell);

	Player(Field* field, ePlayerColor color, PlayerController* playerController);
public:
	ePlayerColor GetPlayerColor() { return mPlayerColor; }
	bool IsReadyToMove() { return mIsReadyToMove; }
	void SetIsReadyToMove(const bool ready) { mIsReadyToMove = ready; }
	virtual bool IsHuman() = 0;
	virtual void MakeMove(Cell* cell) = 0;
};

class Human : public Player
{

public:
	Human(Field* field, ePlayerColor color, PlayerController* playerController);
	virtual bool IsHuman() { return true; }
	virtual void MakeMove(Cell* cell);
};

class Computer : public Player
{
public:
	Computer(Field* field, ePlayerColor color, PlayerController* playerController);
	virtual bool IsHuman() { return false; }
	virtual void MakeMove(Cell* cell) override {}
};
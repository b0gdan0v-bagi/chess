#pragma once
#include "Utils.h"
#include "field.h"

class Player
{
protected:
	ePlayerColor mPlayerColor;
	Field* mField;
	bool mIsReadyToMove;
	Player(Field* field, ePlayerColor color);
public:
	ePlayerColor GetPlayerColor() { return mPlayerColor; }
	bool IsReadyToMove() { return mIsReadyToMove; }
	void SetIsReadyToMove(const bool ready) { mIsReadyToMove = ready; }
	virtual bool IsHuman() = 0;
};

class Human : public Player
{
public:
	Human(Field* field, ePlayerColor color);
	virtual bool IsHuman() { return true; }
};

class Computer : public Player
{
public:
	Computer(Field* field, ePlayerColor color);
	virtual bool IsHuman() { return false; }
	void MakeMove() {}
};
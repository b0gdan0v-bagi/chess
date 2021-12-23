#pragma once
#include "Utils.h"
#include "field.h"

class Player
{
protected:
	ePlayerColor mPlayerColor;
	Field* mField;
	Player(Field* field, ePlayerColor color);
};

class Human : public Player
{
public:
	Human(Field* field, ePlayerColor color);
};

class Computer : public Player
{
public:
	Computer(Field* field, ePlayerColor color);
};
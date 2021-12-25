#pragma once

#include "figure.h"


class Pawn : public Figure
{
	//virtual void DrawSelf() override {};
	//virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(GameEventBase* event) override { return false; };
public:
	Pawn(sf::RenderWindow* window, ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos);

	std::vector<Cell*> GetPossibleCells();
};




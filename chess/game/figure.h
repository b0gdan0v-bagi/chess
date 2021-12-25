#pragma once

#include "Entity.h"
#include "Utils.h"
#include "cell.h"

class Cell;

class Figure : public Entity
{
	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override;
	virtual bool OnEventSelf(GameEventBase* event) override { return false; };
protected:
	sf::Sprite mSprite;
	sf::Vector2f mScale;
	sf::Vector2f mPos;
	ePlayerColor mPlayerColor;

	Cell* mCell;

public:
	Figure(sf::RenderWindow* window, ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos);

	ePlayerColor GetPlayerColor() { return mPlayerColor; }
	void SetCell(Cell* cell) { mCell = cell; }
	Cell* GetCell() { return mCell; }

	virtual std::vector<Cell*> GetPossibleCells() = 0;
};




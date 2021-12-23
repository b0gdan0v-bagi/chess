#pragma once

#include "Entity.h"
#include "cell.h"
#include "Utils.h"
#include "playerController.h"

class Listener;
class PlayerController;

class Field 
	: public Entity
	, public Listener
{
	friend class Engine;
	
	size_t mFieldSize;
	std::vector<Cell*> mCellsData;
	std::vector<Cell*> mPotentialCells;
	Cell* mSelectedCell;

	sf::Vector2f mCellSize;
	sf::Vector2f mPlayFieldSize;
	sf::Vector2f mTextIndentSize;
	sf::Vector2f mResoultion;

	PlayerController* mPlayerController;

	void CreateCells();
	void CreateLabels();
	void CreateFigures();

	void OnEnded();

	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override;
	virtual bool OnEventSelf(GameEventBase* event) override;
public:
	Field(sf::RenderWindow* window, const sf::Vector2f resolution);
	~Field();

	virtual void TakeEvent(GameEventBase* event) override { OnEvent(event); }
	Cell* GetCell(const int x, const int y);
	Cell* GetCell(Cell* cell, eDirection dir);
	Cell* GetCell(sf::Vector2i v) { return GetCell(v.x, v.y); }
	std::vector<Cell*> GetFreeCells(Cell* cell);

	void UnselectCells();
	sf::Vector2i GetCoordFromMouse(const sf::Vector2i mouse);
	Cell* ClickedAvaliableCell(Cell* cell);
};




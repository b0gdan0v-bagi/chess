#pragma once

#include "Entity.h"
#include "cell.h"
#include "Utils.h"


class Field : public Entity
{
	friend class Engine;
	
	size_t mFieldSize;
	std::vector<Cell*> mCellsData;
	sf::Vector2f mCellSize;
	sf::Vector2f mPlayFieldSize;
	sf::Vector2f mTextIndentSize;

	void CreateCells();
	void CreateLabels();
	void CreateFigures();

	void OnEnded();

	std::vector<sf::Text*> mLabels;

	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(sf::Event event) override { return false; };
public:
	Field(sf::RenderWindow* window, const sf::Vector2f resolution);
	~Field();
	Cell* GetCell(const int x, const int y);
	Cell* GetCell(Cell* cell, eDirection dir);
};




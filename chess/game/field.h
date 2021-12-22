#pragma once

#include "Entity.h"
#include "cell.h"


class Field : public Entity
{
	friend class Engine;
	
	const int mFieldSize = 2;
	std::vector<Cell*> mCellsData;
	sf::Vector2f mCellSize;

	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(sf::Event event) override { return false; };
public:
	Field(sf::RenderWindow* window, const sf::Vector2f resolution);
};




#pragma once

#include "Entity.h"
#include "figure.h"

class Field;
class Figure;

class Cell : public Entity
{
	const Field* mField;
	const sf::Vector2i mCoord;
	sf::Color mColor;

	Figure* mFigure;

	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override;
	virtual bool OnEventSelf(sf::Event event) override { return false; };
public:
	Cell(const Field* field, sf::RenderWindow* window, const sf::Vector2f size, const sf::Vector2i coord);
	void SetColor(sf::Color color) { mColor = color; }
	const sf::Vector2i GetCoord() { return mCoord; };
	void SetFigure(Figure* figure);
};




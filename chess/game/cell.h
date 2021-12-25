#pragma once

#include "Entity.h"
#include "figure.h"

class Field;
class Figure;

class Cell : public Entity
{
	Field* mField;
	const sf::Vector2i mCoord;
	sf::Color mColor;

	bool mSelected;

	Figure* mFigure;

	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override;
	virtual bool OnEventSelf(GameEventBase* event) override { return false; };
public:
	Cell(Field* field, sf::RenderWindow* window, const sf::Vector2f size, const sf::Vector2i coord);
	void SetColor(sf::Color color) { mColor = color; }
	const sf::Vector2i GetCoord() { return mCoord; };
	void SetFigure(Figure* figure);
	void UnsetFigure();
	bool HasFigure();
	Figure* GetFigure() { return mFigure; }

	Field* GetField() { return mField; }

	void SetSelected(bool selected) { mSelected = selected; }
	bool IsSelected() { return mSelected; }
};




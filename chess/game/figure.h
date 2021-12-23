#pragma once

#include "Entity.h"
#include "Utils.h"


class Figure : public Entity
{

	virtual void DrawSelf() override {};
	virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(sf::Event event) override { return false; };
protected:
	sf::Sprite mSprite;
	sf::Vector2f mScale;
	ePlayerColor mPlayerColor;

public:
	Figure(sf::RenderWindow* window, ePlayerColor color);
};




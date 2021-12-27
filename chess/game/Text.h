#pragma once

#include "Entity.h"
#include "SFML/Graphics.hpp"


class Text : public Entity
{
	sf::Font mFont;
	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(GameEventBase* event) override { return false; };
public:
	Text(const std::string& name, const sf::Vector2f coord, sf::Font font);
};
#pragma once

#include "Entity.h"
#include "SFML/Graphics.hpp"


class Text : public Entity
{
	sf::Font mFont;
	virtual void DrawSelf() override;
	virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(sf::Event event) override { return false; };
public:
	Text(sf::RenderWindow* window, const std::string& name, const sf::Vector2f coord, sf::Font font);
};
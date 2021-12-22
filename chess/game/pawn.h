#pragma once

#include "figure.h"


class Pawn : public Figure
{
	virtual void DrawSelf() override {};
	virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(sf::Event event) override { return false; };
};




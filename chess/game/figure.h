#pragma once

#include "Entity.h"


class Figure : public Entity
{
	virtual void DrawSelf() override {};
	virtual void UpdateSelf(const float dt) override {};
	virtual bool OnEventSelf(sf::Event event) override { return false; };
};




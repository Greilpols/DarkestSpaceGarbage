#pragma once

#include "Components.hpp"
#include "Vector2D.hpp"

// note to self: Only struct has default public, class has default private
// could just as well be a struct

class PositionComponent : public Component
{

public:

	Vector2D position;

	PositionComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	PositionComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void update() override
	{

	}
};
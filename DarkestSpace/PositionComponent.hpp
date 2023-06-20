#pragma once

#include "Components.hpp"
#include "Vector2D.hpp"

// note to self: Only struct has default public, class has default private
// could just as well be a struct

class PositionComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 2;

	PositionComponent()
	{
		position.Zero();
	}

	PositionComponent(int sc)
	{
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	PositionComponent(float x, float y)
	{
		position.Zero();
	}

	PositionComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		
	}
};
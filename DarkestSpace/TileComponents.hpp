#pragma once

#include "ECS.hpp"
#include "PositionComponent.hpp"
#include <SDL.h>

class TileComponent : Component
{
	PositionComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "water.png";
			break;
		case 1:
			path = "grass.png";
			break;
		case 2:
			path = "dirt.png";
			break;
		default:
			break;
		}
	}
};
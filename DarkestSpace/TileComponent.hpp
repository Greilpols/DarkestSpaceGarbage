#pragma once

#include "ECS.hpp"
#include "PositionComponent.hpp"
#include <SDL.h>

class TileComponent : public Component
{
public:
	PositionComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

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

	void init() override
	{
		entity->addComponent<PositionComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<PositionComponent>();

		entity->addComponent<SpriteComponent>(path);	// fix case if no path is set
		sprite = &entity->getComponent<SpriteComponent>();
	}
};
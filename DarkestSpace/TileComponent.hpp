#pragma once

#include "ECS.hpp"
#include <SDL.h>

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32; //tilesize

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 32;
	}
};
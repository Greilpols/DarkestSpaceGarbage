#pragma once

#include "Components.hpp"
#include "../../SDL2/include/SDL.h"
#include "TextureManager.hpp"

class SpriteComponent : public Component
{
private:
	PositionComponent *position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;		//frames in total
	int speed = 100;	//delay between frames in ms
	
public:

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}


	SpriteComponent(const char* path, int nFrames, int mSpeed)
	{
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = position->height;
		srcRect.w = position->width;
		destRect.w = destRect.y = 64;
	}

	void update() override
	{

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		destRect.x = static_cast<int>(position->position.x);
		destRect.y = static_cast<int>(position->position.y);
		destRect.w = position->width * position->scale;
		destRect.h = position->height * position->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}


};
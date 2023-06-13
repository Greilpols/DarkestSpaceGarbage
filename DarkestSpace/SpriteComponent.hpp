#pragma once

#include "Components.hpp"
#include "../../SDL2/include/SDL.h"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <map>

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

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	//SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	//TODO: Fix this so can flip animations (i.e. no moonwalking walk animations)

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}


	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

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

		srcRect.y = animIndex * position->height;

		destRect.x = static_cast<int>(position->position.x);
		destRect.y = static_cast<int>(position->position.y);
		destRect.w = position->width * position->scale;
		destRect.h = position->height * position->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

	// cycling through the anim pieces to create the animation
	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}


};
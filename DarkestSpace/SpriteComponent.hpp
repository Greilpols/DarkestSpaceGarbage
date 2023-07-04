#pragma once

#include "Components.hpp"
#include "../../SDL2/include/SDL.h"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <map>
#include "AssetManager.hpp"

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

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}


	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 5, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		setTexture(id);
	}

	~SpriteComponent()
	{
	}

	void setTexture(std::string id)
	{
		texture = Game::assets->GetTexture(id);
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

		destRect.x = static_cast<int>(position->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(position->position.y) - Game::camera.y;
		destRect.w = position->width * position->scale;
		destRect.h = position->height * position->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	// cycling through the anim pieces to create the animation
	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}


};
#pragma once
#include <string>
#include <SDL.h>
#include "Components.hpp"
#include "TextureManager.hpp"

class ColliderComponent : public Component
{
public:

	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	PositionComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<PositionComponent>())
		{
			entity->addComponent<PositionComponent>();
		}
		transform = &entity->getComponent<PositionComponent>();

		tex = TextureManager::LoadTexture("assets/test.png");
		srcR = { 0, 0, 32, 32 };
		destR = { collider.x, collider.y, collider.w, collider.h };

		Game::colliders.push_back(this);
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.x = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};
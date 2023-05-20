#pragma once

#include "Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component
{
public:
	PositionComponent* transform;

	void init() override
	{
		transform = &entity->getComponent<PositionComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{}

		if (Game::event.type == SDL_KEYUP)
		{}
	}
};
#pragma once
#include <string>
#include "SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component
{
public:

	SDL_Rect Collider;
	std::string tag;

	PositionComponent* transform;

	void init() override
	{
		if (!entity->hasComponent<PositionComponent>())
		{
			entity->addComponent<PositionComponent>();
		}
		transform = &entity->getComponent<PositionComponent>();
	}

};
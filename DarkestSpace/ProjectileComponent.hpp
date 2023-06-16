#pragma once

#include "ECS.hpp"
#include "Components.hpp"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int range, int speed) : range(range), speed(speed)
	{}
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<PositionComponent>();
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			entity->destroy();
		}
		// WIP:: else if (transform->position.x [....] ); // check if out of map
	}

private:

	PositionComponent* transform;

	int range;
	int speed;
	int distance;
};
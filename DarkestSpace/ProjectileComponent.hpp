#pragma once

#include "ECS.hpp"
#include "Components.hpp"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int range, int speed, Vector2D velocity) : range(range), speed(speed), velocity(velocity)
	{}
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<PositionComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "Out of range" << std::endl;
			entity->destroy();
		}
		// WIP:: else if (transform->position.x [....] ); // check if out of map
	}

private:

	PositionComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};
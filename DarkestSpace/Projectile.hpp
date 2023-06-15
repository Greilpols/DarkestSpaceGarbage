#pragma once

#include "ECS.hpp"
#include "Components.hpp"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int speed)
	{}
	~ProjectileComponent();

	void init() override
	{}

	void update() override
	{}

private:

	PositionComponent* transform;

	int range;
	int speed;
	int distance;
};
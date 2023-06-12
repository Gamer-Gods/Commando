#pragma once
#include "Sprite.h"


class Blaster
{
public:
	Sprite sprite;
	Vec2 velocity;


	//move bullet
	void Update(float deltaTime)
	{
		sprite.position.x += velocity.x * deltaTime;
		sprite.position.y += velocity.y * deltaTime;
	}
};
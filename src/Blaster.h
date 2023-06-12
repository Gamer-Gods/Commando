#pragma once
#include <iostream>
#include "Sprite.h"
#include <vector>
#include "Vec2.h"

constexpr float FPS = 60.0f;
float deltaTime = 1 / FPS; //time passing between frames in seconds


class Blaster
{
public:
	Sprite sprite;
	Vec2 velocity;


	//move bullet
	void Update()
	{
		sprite.position.x += velocity.x * deltaTime;
		sprite.position.y += velocity.y * deltaTime;
	}
};
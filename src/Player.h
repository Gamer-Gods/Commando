#pragma once
#include <SDL_Image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "Blaster.h"

constexpr float FPS = 60.0f;
float deltaTime = 1 / FPS; //time passing between frames in seconds

class Player
{
private:
	float fireRepeatTimer = 0.0f;
public:
	Sprite sprite;
	float moveSpeedPx = 500;
	float fireRepeatDelay = 0.5f;
	float shipHealth = 10;

	// Current Version only handles shooting up or down

	void RestShootCoodown()
	{
		fireRepeatTimer = fireRepeatDelay;
	}
	void Shoot(bool towardUp, std::vector<Blaster>& container, Vec2 velocity)
	{
		//create a new bullet 
		Sprite blasterSprite = Sprite(pRenderer, "../Assets/textures/blasterbolt.png");

		//start blaster at player position
		blasterSprite.position.x = sprite.getPosition().x;
		if (towardUp)
		{
			blasterSprite.position.x += sprite.getSize().x - (sprite.getSize().x / 1.5);
		}
		blasterSprite.position.y = sprite.getPosition().y + (sprite.getSize().y / 2) - (blasterSprite.getSize().y / 2);

		//Set up our blaster class instance
		Blaster blaster;
		blaster.sprite = blasterSprite;
		blaster.velocity = velocity;

		//add blaster to container
		container.push_back(blaster);

		//reset cooldown
		RestShootCoodown();
	}
	void Move(Vec2 input)
	{
		sprite.position.x += input.x * (moveSpeedPx * deltaTime);
		sprite.position.y += input.y * (moveSpeedPx * deltaTime);

	}
	void Update()
	{

		//tick down the time for the shooting cooldown
		fireRepeatTimer -= deltaTime;
	}
	bool CanShoot()
	{
		return(fireRepeatTimer <= 0.0f);
	}
	float GetHealth()
	{
		return(shipHealth);
	}
	void TakeHealth(float h)
	{
		shipHealth = shipHealth - h;
	}
	void SetHealth(float h)
	{
		shipHealth = h;
	}
};
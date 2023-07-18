#pragma once
#include "Blaster.h"
#include <vector>

class Player
{
private:
	float fireRepeatTimer = 0.0f;
	float dodgeImmuneTimer = 0.5f;
	float dodgeRepeatTimer = 0.0f;
	Vec2 goalPos;
public:
	Sprite sprite;
	Vec2 playerDirection = { 0,0 };
	Vec2 playerTilePosition;
	float moveSpeedPx = 500;
	float fireRepeatDelay = 0.5f;
	float shipHealth = 3;
	float dodgeRepeatDelay = 1.0f;
	bool isDodging = false;

	// Current Version only handles shooting up or down

	void RestShootCoodown()
	{
		fireRepeatTimer = fireRepeatDelay;
	}
	void ResetDodgeCooldown()
	{
		dodgeRepeatTimer = dodgeRepeatDelay;
	}
	void Shoot(bool towardUp, std::vector<Blaster>& container, Vec2 velocity, SDL_Renderer* renderer)
	{
		//create a new bullet 
		Sprite blasterSprite = Sprite(renderer, "../Assets/textures/blasterbolt.png");

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
		blaster.velocity.x = velocity.x * 1000;
		blaster.velocity.y = velocity.y * 1000;
		//add blaster to container
		container.push_back(blaster);

		//reset cooldown
		RestShootCoodown();
	}
	void Move(Vec2 input, float deltaTime)
	{
		sprite.position.x += input.x * (moveSpeedPx * deltaTime);
		sprite.position.y += input.y * (moveSpeedPx * deltaTime);

	}
	void MoveLerp(Vec2 Pos, float lerpTime)
	{
		if (!isDodging)
		{
			goalPos = Pos;
		}
		sprite.position = lerp(sprite.position, goalPos, lerpTime);
	}
	void Update(float deltaTime)
	{

		//tick down the time for the shooting cooldown
		fireRepeatTimer -= deltaTime;
		dodgeRepeatTimer -= deltaTime;
		if (isDodging)
		{
			dodgeImmuneTimer -= deltaTime;
		}
	}
	bool CanShoot()
	{
		return(fireRepeatTimer <= 0.0f);
	}
	bool CanDodge()
	{
		return(dodgeRepeatTimer <= 0.0f);
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
	bool startDodge()
	{
		goalPos = playerTilePosition + (playerDirection * 2.0f);
		isDodging = true;
		return isDodging;
	}
	bool duringDodge()
	{
		if (dodgeImmuneTimer <= 0.0f)
		{
			isDodging = false;
		}
		return isDodging;
	}
	void endDodge()
	{
		dodgeImmuneTimer = 0.5f;
		ResetDodgeCooldown();
	}
};
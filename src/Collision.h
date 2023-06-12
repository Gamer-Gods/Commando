#pragma once
#include <SDL_Image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Sprite.h"

bool AreBoundsOverlapping(int minA, int maxA, int minB, int maxB)
{
	bool isOverlapping = false;
	if (maxA >= minB && maxA <= maxB) // check if max a is inside of B
	{
		isOverlapping = true;
	}
	if (minA <= maxB && minA >= minB) // check if min a is inside of B
	{
		isOverlapping = true;
	}
	return isOverlapping;
}
// Check collison between two sprites
bool AreSpritesOverlapping(const Sprite& A, const Sprite& B)
{
	// get bounds of each sprite on x and y
	int minAx, maxAx, minBx, maxBx;
	int minAy, maxAy, minBy, maxBy;

	SDL_Rect boundsA = A.GetRect();
	SDL_Rect boundsB = B.GetRect();

	SDL_bool isColliding = SDL_HasIntersection(&boundsA, &boundsB);
	return (bool)isColliding;

}
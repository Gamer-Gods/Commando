#pragma once
#include <SDL_Image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Vec2.h"

SDL_Renderer* pRenderer = nullptr;
struct Sprite
{
private:
	// public fields can be accessed from outside the struct or class
	SDL_Texture* pTexture;
	SDL_Rect src;
	SDL_Rect dst;

public:

	double rotation = 0; //in degrees
	SDL_RendererFlip flipState = SDL_FLIP_NONE;
	Vec2 position; //where sprite is on screen

	//This is a constructor. this is a special type of function used when creating an object
	//The compiler knows it's a constructor because it has parentheses like a function, has the SAME NAME as the struct or class, and has no return. This one has no arguments. In that case, it's called the default constructor and is used to set default values.
	Sprite()
	{
		//std::cout << "Sprite default constructor\n";
		pTexture = nullptr;
		src = SDL_Rect{ 0,0,0,0 };
		dst = SDL_Rect{ 0,0,0,0 };
	}
	//UI Sprite From Text
	Sprite(TTF_Font* font, const char* text, SDL_Color color) : Sprite()
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
		pTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
		SDL_FreeSurface(surface);
		TTF_SizeText(font, text, &dst.w, &dst.h);
		src.w = dst.w;
		src.h = dst.h;

	}

	//constructors can have arguments as well, which is handy when we need to make them different
	Sprite(SDL_Renderer* renderer, const char* filePathToLoad)
	{
		//std::cout << "Sprite filepath constructor\n";
		src = SDL_Rect{ 0,0,0,0 };

		pTexture = IMG_LoadTexture(renderer, filePathToLoad); //load into our pTexture pointer
		if (pTexture == NULL)
		{
			std::cout << "Image failed to load: " << SDL_GetError() << std::endl;
		}
		SDL_QueryTexture(pTexture, NULL, NULL, &src.w, &src.h); //ask for the dimensions of the texture
		dst = SDL_Rect{ 0,0,src.w,src.h };
		//at this point, the width and the height of the texture should be placed at the memory addresses of src.w and src.h
	}

	//getters and setters

	//sets size for width and height
	void setSize(Vec2 sizeWidthHeight)
	{
		dst.w = sizeWidthHeight.x;
		dst.h = sizeWidthHeight.y;
	}

	//sets width and height
	void setSize(int w, int h)
	{
		dst.w = w;
		dst.h = h;
	}

	SDL_Rect GetRect() const //this function does not change anything
	{
		SDL_Rect returnValue = dst;
		returnValue.x = position.x;
		returnValue.y = position.y;
		return dst;
	}

	//return width and height
	Vec2 getSize() const
	{
		Vec2 returnVec = { dst.w,dst.h };
		return returnVec;
	}

	//return x and y position
	Vec2 getPosition()
	{
		Vec2 returnVec = { dst.x,dst.y };
		return returnVec;
	}


	//this draw function can be called on individual varuables of type Sprite, which will use their own variables to call SDL_RenderCopy. So, we can declare and draw new sprites with two lines:
	//Sprite myNewSprite = Sprite(pRenderer, "somefile.png");
	//myNewSprite.Draw(pRenderer);
	void Draw(SDL_Renderer* renderer)
	{
		dst.x = position.x;
		dst.y = position.y;
		SDL_RenderCopyEx(renderer, pTexture, &src, &dst, rotation, NULL, flipState);
	}

	void Cleanup()
	{
		SDL_DestroyTexture(pTexture);
		std::cout << SDL_GetError();
	}

};
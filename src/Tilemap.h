#pragma once
#include <iostream>
#include <SDL.h>
//Tilemap holds a grid of tiles, which may be floors or walls
//Draw different tiles of the game world
#define TILEMAP_WIDTH 5
#define TILEMAP_HEIGHT 5

enum Tile
{
	Floor = 0,
	Wall,
	Trap,
	Idk,
	WhateverTileTypesYouWant,
	Count
};

class Tilemap
{
public:
	int tileWidth = 32;
	int tileHeight = 32;

	Tile tiles[TILEMAP_WIDTH][TILEMAP_HEIGHT]; // 2D array holding the types and positions of tiles in the world. The positions are implied by their place in the array
	/*
	[
	[0,1,2,3... TILEMAP_HEIGHT],
	[0,1,2,3... TILEMAP_HEIGHT],
	...
	[0,1,2,3... TILEMAP_HEIGHT]
	]
	*/

private:

	//An array of textures could be used to index different textures based on the tile type found in tiles[][] 
	SDL_Texture* pTileTextures[Count];

public:
	Tilemap()
	{
		for (int x = 0; x < TILEMAP_WIDTH; x++)
		{
			for (int y = 0; y < TILEMAP_HEIGHT; y++)
			{
				tiles[x][y] = Floor;
			}
		}
		//tiles[8][5] = Wall;
	}

	void LoadTextureForTile(Tile tileType, const char* textureFilePath)
	{
		pTileTextures[tileType] = IMG_LoadTexture(pRenderer, textureFilePath);
	}

	void LoadLevelFromFile(const char* levelFilePath)
	{
		// TODO: add some way to load a file in as a level e.g. make a text file of ASCII art, intepret the characters in the ASCII art as different Tile Types
		/* Might come as a file "level.txt" that just looks like this: 
			XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			X..P...................................O.X
			XXXXXX..........XXXXXXXXXXXXXXXXXXXXXXXXXX
			XXXXXXXXXXX..............................X
			XXXXXXXXXXXXXXXXXXXX.....................X
			XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		*/ // Where P is the player start tile, "X" are walls, "." are floors, AND "O" is the goal or a door to the next level 
	}

	void Draw(SDL_Renderer* renderer)
	{
		for (int x = 0; x < TILEMAP_WIDTH; x++)
		{
			for (int y = 0; y < TILEMAP_HEIGHT; y++)
			{
				//std::cout << "tile: " << tiles[x][y];
				SDL_Rect src = { 0,0,tileWidth,tileHeight };
				SDL_Rect dst = src;

				//Draw floor tile on screen at x,y
				dst.x = x * tileWidth;
				dst.y = y * tileHeight;

				Tile tileType = tiles[x][y];
				SDL_RenderCopy(renderer, pTileTextures[tileType], &src, &dst);
			}
		}
	}
};
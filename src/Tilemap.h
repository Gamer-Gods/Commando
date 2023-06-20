#pragma once
#include "Vec2.h"
#include <iostream>
#include <SDL.h>
//Tilemap holds a grid of tiles, which may be floors or walls
//Draw different tiles of the game world
#define TILEMAP_WIDTH 10
#define TILEMAP_HEIGHT 10

enum Tile
{
	F = 0,
	W = 1,
	Count
};

class Tilemap
{
public:
	int tileWidthPx = 90;
	int tileHeightPx = 64;

	Tile tiles[TILEMAP_WIDTH][TILEMAP_HEIGHT] = {   {W,W,W,F,F,W,W,W,F,F,},
													{F,F,W,F,F,F,F,W,F,F,},
													{F,F,W,F,F,F,F,W,F,F,},
													{F,F,F,F,F,F,F,F,F,F,},
													{F,F,F,F,F,F,F,F,F,F,}, 
													{W,W,W,F,F,W,W,W,F,F,}, 
													{F,F,W,F,F,F,F,W,F,F,},
													{F,F,W,F,F,F,F,W,F,F,},
													{F,F,F,F,F,F,F,F,F,F,},
													{F,F,F,F,F,F,F,F,F,F,}
	
	}; // 2D array holding the types and positions of tiles in the world. The positions are implied by their place in the array
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
		//for (int x = 0; x < TILEMAP_WIDTH; x++)
		//{
		//	for (int y = 0; y < TILEMAP_HEIGHT; y++)
		//	{
		//		tiles[x][y] = F;
		//	}
		//}


		//tiles[8][5] = W;
	}

	void LoadTextureForTile(Tile tileType, SDL_Renderer* pRenderer, const char* textureFilePath)
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

	Vec2 TileContainingScreenPos(int x, int y)
	{
		Vec2 ret;
		ret.x = x / tileWidthPx;
		ret.y = y / tileHeightPx;
		return ret;
	}

	Vec2 ScreenPosOfTile(int x, int y)
	{
		Vec2 ret;
		ret.x = x * tileWidthPx;
		ret.y = y * tileHeightPx;
		return ret;
	}

	Tile GetTile(int x, int y)
	{
		return tiles[x][y];
	}

	Tile GetTile(Vec2 pos)
	{
		return tiles[(int)pos.x][(int)pos.y];
	}

	void Draw(SDL_Renderer* renderer)
	{
		for (int x = 0; x < TILEMAP_WIDTH; x++)
		{
			for (int y = 0; y < TILEMAP_HEIGHT; y++)
			{
				//std::cout << "tile: " << tiles[x][y];
				SDL_Rect src = { 0,0,tileWidthPx,tileHeightPx };
				SDL_Rect dst = src;

				//Draw floor tile on screen at x,y

				Vec2 screenPos = ScreenPosOfTile(x, y);
				dst.x = screenPos.x;
				dst.y = screenPos.y;

				Tile tileType = tiles[x][y];
				SDL_RenderCopy(renderer, pTileTextures[tileType], &src, &dst);
			}
		}
	}

	
};
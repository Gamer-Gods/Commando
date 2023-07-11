#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Vec2.h"
//Tilemap holds a grid of tiles, which may be floors or walls
//Draw different tiles of the game world
#define MAP_WIDTH 30
#define MAP_HEIGHT 15

enum class Tile
{
	Floor = 0,
	Walls,
	Trap,
	Start,
	Goals,
	Count
};
const Vec2 NORTH = { 0,-1 };
const Vec2 SOUTH = { 0,1 };
const Vec2 EAST = { 1,0 };
const Vec2 WEST = { -1,0 };

struct TileCoord
{
	int x = 0;
	int y = 0;

	TileCoord()
	{

	}
	TileCoord(int ax, int ay)
	{
		x = ax;
		y = ay;
	}
	TileCoord(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	TileCoord(Vec2 position)
	{
		x = (int)position.x;
		y = (int)position.y;
	}
	Vec2 toVec2() const
	{
		return Vec2{ (float)x, (float)y };
	}
};

bool operator!=(const TileCoord& l, const TileCoord& r)
{
	return l.x != r.x || l.y != r.y;
}
bool operator==(const TileCoord& l, const TileCoord& r)
{
	return l.x == r.x && l.y == r.y;
}

TileCoord operator+(const TileCoord& l, const TileCoord& r)
{
	return { l.x + r.x, l.y + r.y };
}
TileCoord operator-(const TileCoord& l, const TileCoord& r)
{
	return { l.x - r.x, l.y - r.y };
}

TileCoord operator*(const TileCoord& l, const int& r)
{
	return { l.x * r, l.y * r };
}
TileCoord operator/(const TileCoord& l, const int& r)
{
	return { l.x / r, l.y / r };
}



class Tilemap
{
private:

	//An array of textures could be used to index different textures based on the tile type found in tiles[][] 
	SDL_Texture* tileTextures[(int)Tile::Count];

	Tile tiles[MAP_WIDTH][MAP_HEIGHT];

public:
	int tileSizeX = 40;
	int tileSizeY = 40;
	Tile tilemap[MAP_WIDTH][MAP_HEIGHT] = {
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls },
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Start, Tile::Start, Tile::Start, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Start, Tile::Start, Tile::Start, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Walls, Tile::Walls, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Goals, Tile::Goals, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Floor, Tile::Floor, Tile::Goals, Tile::Goals, Tile::Walls},
		{Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls, Tile::Walls},
	};
	Tilemap()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				tiles[x][y] = GetTile(x, y);
			}
		}
		//tiles[8][5] = Walls;
	}

	void LoadTextureForTile(Tile tileType, const char* textureFilePath, SDL_Renderer* pRenderer)
	{
		tileTextures[(int)tileType] = IMG_LoadTexture(pRenderer, textureFilePath);
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
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				Tile tileType = GetTile(x, y);
				Vec2 tilePosition = TilePosToScreenPos(x, y);
				SDL_Texture* tex = tileTextures[(int)tileType];
				//std::cout << "tile: " << tiles[x][y];
				SDL_Rect src = { 0,0,tileSizeX,tileSizeY };
				SDL_Rect dst = { tilePosition.x, tilePosition.y, tileSizeX,tileSizeY };

				//Draw floor tile on screen at x,y
				dst.x = x * tileSizeX;
				dst.y = y * tileSizeY;


				if (SDL_RenderCopy(renderer, tex, &src, &dst) != 0)
				{
					std::cout << SDL_GetError() << std::endl;
				}
			}
		}
	}
	Vec2 GetScreenPosOfTile(TileCoord tilePostion)
	{
		return Vec2{ (float)tilePostion.x * tileSizeX, (float)tilePostion.y * tileSizeY };
	}
	TileCoord GetTileAtScreenPos(Vec2 positionOnScreen)
	{
		return { floorf(positionOnScreen.x / tileSizeX),floorf(positionOnScreen.y / tileSizeY) };
	}
	bool IsTileTreversable()
	{
		//checks if its inside tile map and if its a wall
		return true;
	}

	int GetGridWidth();
	int GetGridHeight();
	Tile GetTile(int x, int y)
	{
		Tile tile = tilemap[x][y];
		return tile;
	}
	void SetTile(int x, int y, Tile type);
	bool IsInsideGrid(int x, int y);
	Vec2 TilePostoScreenPos(Vec2 tilePostion);
	Vec2 TilePosToScreenPos(float x, float y)
	{
		return { (x * MAP_WIDTH), (y * MAP_HEIGHT) };
	}
	Vec2 ScreenPostoTilePos(Vec2 positionOnScreen);
};
//file:///C:/Users/capta/Downloads/AI_Lab_4.docx_1.pdf
//add center function
//player position on tilegrid
//if player can be here
//if (level.tiles[3][3] == Walls)
//{
//	
//}
#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Vec2.h"
//Tilemap holds a grid of tiles, which may be floors or walls
//Draw different tiles of the game world
#define MAP_WIDTH 30
#define MAP_HEIGHT 15

enum Tile
{
	f = 0,
	W,
	T,
	S,
	G,
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


Vec2 operator+(const Vec2& l, const Vec2& r)
{
	return { l.x + r.x, l.y + r.y };
}
Vec2 operator-(const Vec2& l, const Vec2& r)
{
	return { l.x - r.x, l.y - r.y };
}

bool operator!=(const Vec2& l, const Vec2& r)
{
	return l.x != r.x || l.y != r.y;
}
bool operator==(const Vec2& l, const Vec2& r)
{
	return l.x == r.x && l.y == r.y;
}

Vec2 operator*(const Vec2& l, const int& r)
{
	return { l.x * r, l.y * r };
}
Vec2 operator/(const Vec2& l, const int& r)
{
	return { l.x / r, l.y / r };
}

Vec2 operator*(const Vec2& l, const float& r)
{
	return { l.x * r, l.y * r };
}
Vec2 operator/(const Vec2& l, const float& r)
{
	return { l.x / r, l.y / r };
}

Vec2 lerp(Vec2 a, Vec2 b, float t)
{
	return a * (1.0f - t) + b * t;
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
	int tilemap[MAP_WIDTH][MAP_HEIGHT] = {
		{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, S, S, S, W, W, W, W, W, W},
		{W, W, W, W, W, W, S, S, S, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, f, f, f, f, W, W, W},
		{W, W, W, W, W, W, f, f, f, f, f, f, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, W, W, W, W, f, f, W, W, W, W, W, W, W},
		{W, W, f, f, f, f, f, f, W, W, W, W, W, W, W},
		{W, W, f, f, f, f, f, f, W, W, W, W, W, W, W},
		{W, W, f, f, W, W, W, W, W, W, W, W, W, W, W},
		{W, W, f, f, W, W, W, W, W, W, W, W, W, W, W},
		{W, W, f, f, f, f, f, f, f, f, f, f, W, W, W},
		{W, W, f, f, f, f, f, f, f, f, f, f, W, W, W},
		{W, W, f, f, W, W, W, W, W, W, f, f, W, W, W},
		{W, W, f, f, W, W, W, W, W, W, f, f, W, W, W},
		{W, W, f, f, W, W, W, W, W, W, f, f, W, W, W},
		{W, W, f, f, W, W, W, W, W, W, f, f, W, W, W},
		{W, W, f, f, f, f, f, f, W, W, f, f, W, W, W},
		{W, W, f, f, f, f, f, f, W, W, f, f, W, W, W},
		{W, W, W, W, W, W, W, W, W, W, f, f, G, G, W},
		{W, W, W, W, W, W, W, W, W, W, f, f, G, G, W},
		{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
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
		//tiles[8][5] = W;
	}

	void LoadTextureForTile(Tile tileType, const char* textureFilePath, SDL_Renderer* pRenderer)
	{
		tileTextures[tileType] = IMG_LoadTexture(pRenderer, textureFilePath);

		if (tileType)
		{
			std::cout << tileType;
		}
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
	bool IsTraversible(Vec2 tilePosition)
	{
		//checks if its inside tile map and if its a wall
		if (IsInsideLevel(tilePosition))
		{
			Tile Traverse = GetTile(tilePosition.x, tilePosition.y);
			if (Traverse != W)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	int GetGridWidth();
	int GetGridHeight();
	Tile GetTile(int x, int y)
	{
		Tile tile = (Tile)tilemap[x][y];
		return tile;
	}
	Tile GetTile(Vec2 coords)
	{
		int x = coords.x;
		int y = coords.y;
		Tile tile = (Tile)tilemap[x][y];
		return tile;
	}
	void SetTile(int x, int y, Tile type)
	{
		tilemap[x][y] = type;
	}
	bool IsInsideGrid(int x, int y);
	bool IsInsideLevel(Vec2 tilePosition)
	{
		if ((tilePosition.x < MAP_WIDTH) || (tilePosition.x > 0))
		{
			if (tilePosition.y < (MAP_HEIGHT) || tilePosition.y > 0)
			{
				return true;
			}
		}
		return false;
	}
	Vec2 TilePosToScreenPos(Vec2 tilePostion)
	{
		return { (tilePostion.x * tileSizeX), (tilePostion.y * tileSizeY) };
	}
	Vec2 TilePosToScreenPos(float x, float y)
	{
		return { (x * tileSizeX), (y * tileSizeY) };
	}
	Vec2 ScreenPostoTilePos(Vec2 positionOnScreen)
	{
		return { (positionOnScreen.x / tileSizeX), (positionOnScreen.y / tileSizeY) };
	}

	std::vector<Vec2> GetTraversibleTilesAdjacentTo(Vec2 tilePos)
	{
		std::vector<Vec2> adjacentTilePositions;
		//North, South, East, West
		Vec2 N = tilePos + NORTH;
		Vec2 S = tilePos + SOUTH;
		Vec2 E = tilePos + EAST;
		Vec2 W = tilePos + WEST;

		if (IsTraversible(N))
		{
			adjacentTilePositions.push_back(N);
		}
		if (IsTraversible(S))
		{
			adjacentTilePositions.push_back(S);
		}
		if (IsTraversible(E))
		{
			adjacentTilePositions.push_back(E);
		}
		if (IsTraversible(W))
		{
			adjacentTilePositions.push_back(W);
		}
		return adjacentTilePositions;
	}
};
//file:///C:/Users/capta/Downloads/AI_Lab_4.docx_1.pdf
//add center function
//player position on tilegrid
//if player can be here
//if (level.tiles[3][3] == W)
//{
//	
//}
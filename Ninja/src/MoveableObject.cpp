#include "MoveableObject.h"
#include "GameState.h"
#include <vector>
#include <cmath>
#include <iostream>

//using namespace std;

MoveableObject::MoveableObject() {}
// constructeur exhaustif
MoveableObject::MoveableObject(int xPos, int yPos, int xSpeed, int ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite) {
	this->alive = true;
	this->xPos = xPos;
	this->yPos = yPos;
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	this->id = id;
	this->bounds = bounds;
	this->sprite = sprite;
}
// destructeur
MoveableObject::~MoveableObject() {}

// methodes
void MoveableObject::update(float dx, float dy) {
	float wantedXPos = xPos + dx * xSpeed;
	float wantedYPos = yPos + dy * ySpeed;

	float newXPos = wantedXPos;
	float newYPos = wantedYPos;

	int tileWidth = GameState::map->tilesWidth;
	int mapWidth = GameState::map->mapWidth;

	int xTile = xPos / tileWidth;
	int yTile = yPos / tileWidth;

	int detectXcol = 0;
	int detectYcol = 0;

	// Solve X-axis
	if((((int)wantedXPos) < xTile * tileWidth - bounds.x) && (dx < 0)) // Going to the left
	{
		for(int j = -1; j <= 1; j++)
		{
			int x = xTile - 1;
			int y = yTile + j;
			if(x < 0 || x >= mapWidth || y < 0 || y >= 10) continue;
			if(GameState::map->grid[x + mapWidth * y] != 1) continue;
			if(GameState::map->grid[(x + 1) + mapWidth * y] == 1) continue; // Ignore inside walls

			if(((int)wantedYPos) <= (y + 1) * tileWidth - 1 - bounds.y && ((int)wantedYPos) >= y * tileWidth - bounds.y - bounds.h)
			{
				newXPos = xTile * tileWidth - bounds.x;
				detectXcol = -1;
			}
		}
	}
	if((((int)wantedXPos) > (xTile + 1) * tileWidth - 1 - bounds.x - bounds.w) && (dx > 0)) // Going to the right
	{
		for(int j = -1; j <= 1; j++)
		{
			int x = xTile + 1;
			int y = yTile + j;
			if(x < 0 || x >= mapWidth || y < 0 || y >= 10) continue;
			if(GameState::map->grid[x + mapWidth * y] != 1) continue;
			if(GameState::map->grid[(x - 1) + mapWidth * y] == 1) continue; // Ignore inside walls

			if(((int)wantedYPos) <= (y + 1) * tileWidth - 1 - bounds.y && ((int)wantedYPos) >= y * tileWidth - bounds.y - bounds.h)
			{
				newXPos = (xTile + 1) * tileWidth - 1 - bounds.x - bounds.w;
				detectXcol = 1;
			}
		}
	}

	// Solve Y-axis
	if((((int)wantedYPos) < yTile * tileWidth - bounds.y) && (dy < 0)) // Going upward
	{
		for(int i = -1; i <= 1; i++)
		{
			int x = xTile + i;
			int y = yTile - 1;
			if(x < 0 || x >= mapWidth || y < 0 || y >= 10) continue;
			if(GameState::map->grid[x + mapWidth * y] != 1) continue;
			if(GameState::map->grid[x + mapWidth * (y + 1)] == 1) continue; // Ignore inside walls

			if(((int)wantedXPos) <= (x + 1) * tileWidth - 1 - bounds.x && ((int)wantedXPos) >= x * tileWidth - bounds.x - bounds.w)
			{
				newYPos = yTile * tileWidth - bounds.y;
				detectYcol = -1;
			}
		}
	}
	if((((int)wantedYPos) > (yTile + 1) * tileWidth - 1 - bounds.y - bounds.h) && (dy > 0)) // Going downward
	{
		for(int i = -1; i <= 1; i++)
		{
			int x = xTile + i;
			int y = yTile + 1;
			if(x < 0 || x >= mapWidth || y < 0 || y >= 10) continue;
			if(GameState::map->grid[x + mapWidth * y] != 1) continue;
			if(GameState::map->grid[x  + mapWidth * (y - 1)] == 1) continue; // Ignore inside walls

			if(((int)wantedXPos) <= (x + 1) * tileWidth - 1 - bounds.x && ((int)wantedXPos) >= x * tileWidth - bounds.x - bounds.w)
			{
				newYPos = (yTile + 1) * tileWidth - 1 - bounds.y - bounds.h;
				detectYcol = 1;
			}
		}
	}

	if (detectXcol && detectYcol) // Prise en compte des cas pathologiques
	{
		if(detectXcol == -1 && GameState::map->grid[xTile - 1 + mapWidth * yTile] != 1 && dy > 0)
		{
			newXPos = wantedXPos;
		}
		else if(detectXcol == 1 && GameState::map->grid[xTile + 1 + mapWidth * yTile] != 1 && dy > 0)
		{
			newXPos = wantedXPos;
		}
		 else if(detectXcol == -1 && GameState::map->grid[xTile  + mapWidth * (yTile - 1)] != 1 && dy < 0)
		{
			newYPos = wantedYPos;
		}
		else if(detectXcol == 1 && GameState::map->grid[xTile  + mapWidth * (yTile - 1)] != 1 && dy < 0)
		{
			newYPos = wantedYPos;
		}
	}

	xPos = (int)newXPos;
	yPos = (int)newYPos;
}

// accesseurs
int MoveableObject::getId() {return id;}
int MoveableObject::getXPos() {return xPos;}
int MoveableObject::getYPos() {return yPos;}
bool MoveableObject::isAlive() {return alive;}

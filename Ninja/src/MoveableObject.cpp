#include "MoveableObject.h"
#include "GameState.h"
#include <vector>
#include <cmath>
#include <iostream>

//using namespace std;

MoveableObject::MoveableObject() {}
// constructeur exhaustif
MoveableObject::MoveableObject(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite) {
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
	float newXPos = xPos + dx * xSpeed;
	float newYPos = yPos + dy * ySpeed;
/*
	float wantedXPos = xPos + dx * xSpeed;
	float wantedYPos = yPos + dy * ySpeed;

	float newXPos = wantedXPos;
	float newYPos = wantedYPos;


    int xTile = ((int)xPos) / 64;
    int yTile = ((int)yPos) / 64;

    int detectXcol = 0;
    int detectYcol = 0;
    // Solve X-axis
    if((((int)wantedXPos) < xTile * 64 - bounds.x) && (dx < 0)) // Going to the left
    {
        for(int j = -1; j <= 1; j++)
        {
            int x = xTile - 1;
            int y = yTile + j;
            if(x < 0 || x >= 19 || y < 0 || y >= 10) continue;
            if(GameState::map->grid[x + 19 * y] != 1) continue;
            if(GameState::map->grid[(x + 1) + 19 * y] == 1) continue; // Ignore inside walls

            if(((int)wantedYPos) <= (y + 1) * 64 - 1 - bounds.y && ((int)wantedYPos) >= y * 64 - bounds.y - bounds.h)
            {
                newXPos = xTile * 64 - bounds.x;
                detectXcol = -1;
            }
        }
    }
    if((((int)wantedXPos) > (xTile + 1) * 64 - 1 - bounds.x - bounds.w) && (dx > 0)) // Going to the right
    {
        for(int j = -1; j <= 1; j++)
        {
            int x = xTile + 1;
            int y = yTile + j;
            if(x < 0 || x >= 19 || y < 0 || y >= 10) continue;
            if(GameState::map->grid[x + 19 * y] != 1) continue;
            if(GameState::map->grid[(x - 1) + 19 * y] == 1) continue; // Ignore inside walls

            if(((int)wantedYPos) <= (y + 1) * 64 - 1 - bounds.y && ((int)wantedYPos) >= y * 64 - bounds.y - bounds.h)
            {
                newXPos = (xTile + 1) * 64 - 1 - bounds.x - bounds.w;
                detectXcol = 1;
            }
        }
    }

    // Solve Y-axis
    if((((int)wantedYPos) < yTile * 64 - bounds.y) && (dy < 0)) // Going upward
    {
        for(int i = -1; i <= 1; i++)
        {
            int x = xTile + i;
            int y = yTile - 1;
            if(x < 0 || x >= 19 || y < 0 || y >= 10) continue;
            if(GameState::map->grid[x + 19 * y] != 1) continue;
            if(GameState::map->grid[x + 19 * (y + 1)] == 1) continue; // Ignore inside walls

            if(((int)wantedXPos) <= (x + 1) * 64 - 1 - bounds.x && ((int)wantedXPos) >= x * 64 - bounds.x - bounds.w)
            {
                newYPos = yTile * 64 - bounds.y;
                detectYcol = -1;
            }
        }
    }
    if((((int)wantedYPos) > (yTile + 1) * 64 - 1 - bounds.y - bounds.h) && (dy > 0)) // Going downward
    {
        for(int i = -1; i <= 1; i++)
        {
            int x = xTile + i;
            int y = yTile + 1;
            if(x < 0 || x >= 19 || y < 0 || y >= 10) continue;
            if(GameState::map->grid[x + 19 * y] != 1) continue;
            if(GameState::map->grid[x  + 19 * (y - 1)] == 1) continue; // Ignore inside walls

            if(((int)wantedXPos) <= (x + 1) * 64 - 1 - bounds.x && ((int)wantedXPos) >= x * 64 - bounds.x - bounds.w)
            {
                newYPos = (yTile + 1) * 64 - 1 - bounds.y - bounds.h;
                detectYcol = 1;
            }
        }
    }

    if (detectXcol && detectYcol) // Prise en compte des cas pathologiques
    {
        if(detectXcol == -1 && GameState::map->grid[xTile - 1 + 19 * yTile] != 1 && dy > 0)
        {
            newXPos = wantedXPos;
        }
        else if(detectXcol == 1 && GameState::map->grid[xTile + 1 + 19 * yTile] != 1 && dy > 0)
        {
            newXPos = wantedXPos;
        }
         else if(detectXcol == -1 && GameState::map->grid[xTile  + 19 * (yTile - 1)] != 1 && dy < 0)
        {
            newYPos = wantedYPos;
        }
        else if(detectXcol == 1 && GameState::map->grid[xTile  + 19 * (yTile - 1)] != 1 && dy < 0)
        {
            newYPos = wantedYPos;
        }
    }
*/

	// compute the new xPos, yPos in order to 'run' on the Walls (not to be blocked on the wall)
	detectMapCollision(&newXPos, &newYPos);

	xPos = newXPos;
	yPos = newYPos;
}

void MoveableObject::detectMapCollision(float *xPosWanted, float *yPosWanted) {
	int nTiles = GameState::map->mapWidth;
	int tileWidth = GameState::map->tilesWidth;

	std::vector<int> blockCollision = {0,0,0,0};

    int xTile = static_cast<int>((*xPosWanted + bounds.x) / tileWidth);
    int yTile = static_cast<int>((*yPosWanted + bounds.y) / tileWidth);

    //std::cout << xTile << " " << yTile << std::endl;

    uint8_t k = 0;
    for(uint8_t j=0; j<2; j++)
    {	for(uint8_t i=0; i<2; i++)
		{	if(GameState::map->grid[(xTile + i) + nTiles * (yTile + j)] == GameState::map->WALL)
	    	{	// Collision potentielle sur un WALL
				float penDx, penDy;
				SDL_Rect wallRect = {(xTile + i) * tileWidth, (yTile + j) * tileWidth, tileWidth, tileWidth};
				computeDistancePenetration(&penDx, &penDy, *xPosWanted, *yPosWanted, wallRect);
				// Dans un premier temps, gestion des collision uniquement selon 1 axe (x ou y)
				if (penDx == 0)
				{	// collision uniquement selon l'axe y
					*yPosWanted += penDy;
					k += 1;
				}
				else if (penDy == 0)
				{	// collision uniquement selon l'axe x
					*xPosWanted += penDx;
					k += 1;
				} else
				{ // la gestion des collisions selon les deux axes se fera ultérieurement
					blockCollision[k] = 1;
					k++;
				}
	    	} else {k += 1;} // Pas de collision avec bloc actuel, passage au bloc suivant
		}
    }
    // Gestion des collisions selon les deux axes
    k = 0;
    while (k <= 4) // parcours de tout le vector distPen
    {
    	if(blockCollision[k] == 0) {k += 1;} // collision déjà gérée précédement
    	else
    	{
    		uint8_t i,j;
    		switch(k) { // conversion de la valeur de k vers le bon wallRect (i,j)
    			case 0:
    			{
    				i = j = 0;
    			} break;
    			case 1:
    			{
    				i = 1; j = 0;
    			} break;
    			case 2:
    			{
    				i = 0; j = 1;
    			} break;
    			default:
    			{
    				i = j = 1;
    			} break;
    		}
    		SDL_Rect wallRect = {(xTile + i) * tileWidth, (yTile + j) * tileWidth, tileWidth, tileWidth};
    		float penDx, penDy;
    		computeDistancePenetration(&penDx, &penDy, *xPosWanted, *yPosWanted, wallRect);
    		if ((penDx == 0) && (penDy == 0)) {k += 1;} // Plus de collision avec les nouvelles x/yPosWanted, on passe au prochain bloc
    		else
    		{	// on corrige que selon la plus petite pénétration
    			if(abs(penDx) < abs(penDy))
    			{
    				*xPosWanted += penDx;
    			} else
    			{
    				*yPosWanted += penDy;
    			}
    			k += 1; // passage au prochain bloc
    		}
    	}
    }
}

void MoveableObject::computeDistancePenetration(float *penDx, float *penDy, float xPosWanted, float yPosWanted, SDL_Rect wallRect) {
	if((yPos + bounds.y + bounds.h <= wallRect.y) && (wallRect.y < yPosWanted + bounds.y + bounds.h))
	{	// Collision de la face DOWN
		*penDy = -((yPosWanted + bounds.y + bounds.h) - wallRect.y);
	}
	else if((yPos + bounds.y >= wallRect.y + wallRect.h) && (wallRect.y + wallRect.h > yPosWanted + bounds.y))
	{	// Collision de la face UP
		*penDy = (wallRect.y + wallRect.h) - (yPosWanted + bounds.y);
	} else {*penDy = 0;}
	if((xPos + bounds.x + bounds.w <= wallRect.x) && (wallRect.x < xPosWanted + bounds.x + bounds.w))
	{	// Collision de la face RIGHT
		*penDx = -((xPosWanted + bounds.x + bounds.w) - wallRect.x);
	}
	else if((xPos + bounds.x >= wallRect.x + wallRect.w) && (wallRect.x + wallRect.w > xPosWanted + bounds.x))
	{	// Collision de la face LEFT
		*penDx = (wallRect.x + wallRect.w) - (xPosWanted + bounds.x);
	} else {*penDx = 0;}

	std::cout << "xWanted : " << xPosWanted  << " yWanted : " << yPosWanted << " Dx :" << *penDx <<  " Dy :" << *penDy << std::endl;
}


// accesseurs
int MoveableObject::getId() {return id;}
float MoveableObject::getXPos() {return xPos;}
float MoveableObject::getYPos() {return yPos;}
float MoveableObject::getXSpeed() {return xSpeed;}
float MoveableObject::getYSpeed() {return ySpeed;}
bool MoveableObject::isAlive() {return alive;}

#include "MoveableObject.h"
#include "GameState.h"
#include <vector>
#include <cmath>

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

	// compute the new xPos, yPos in order to 'run' on the Walls (not to be blocked on the wall)
	detectMapCollision(&newXPos, &newYPos);

	xPos = newXPos;
	yPos = newYPos;
}

void MoveableObject::detectMapCollision(float *xPosWanted, float *yPosWanted) {
	int nTiles = GameState::map->mapWidth;
	int tileWidth = GameState::map->tilesWidth;

	std::vector<int> distPen = {0,0,0,0,0,0,0,0};

    int xTile = (int)(*xPosWanted / tileWidth);
    int yTile = (int)(*yPosWanted / tileWidth);

    uint8_t k = 0;
    for(uint8_t j=0; j<2; j++)
    {	for(uint8_t i=0; i<2; i++)
		{	if(GameState::map->grid[(xTile + i) + nTiles * (yTile + j)] == GameState::map->WALL)
	    	{	// Collision potentielle sur un WALL
				int penDx, penDy;
				SDL_Rect wallRect = {(xTile + i) * tileWidth, (yTile + j) * tileWidth, tileWidth, tileWidth};
				computeDistancePenetration(&penDx, &penDy, *xPosWanted, *yPosWanted, wallRect);
				// Dans un premier temps, gestion des collision uniquement selon 1 axe (x ou y)
				if (penDx == 0)
				{	// collision uniquement selon l'axe y
					*yPosWanted -= penDy;
					k += 2;
				}
				else if (penDy == 0)
				{	// collision uniquement selon l'axe x
					*xPosWanted -= penDx;
					k += 2;
				} else
				{	// la gestion des collisions selon les deux axes se fera ultérieurement
					distPen[k] = penDx;
					k++;
					distPen[k] = penDy;
					k++;
				}
	    	} else {k += 2;} // Pas de collision avec bloc actuel, passage au bloc suivant
		}
    }
    // Gestion des collisions selon les deux axes
    k = 0;
    while (k <= 8) // parcours de tout le vector distPen
    {
    	if(distPen[k] == 0) {k +=2;} // collision déjà gérée précédement
    	else
    	{
    		uint8_t i,j;
    		switch(k) { // conversion de la valeur de k vers le bon wallRect (i,j)
    			case 0:
    			{
    				i = j = 0;
    			} break;
    			case 2:
    			{
    				i = 1; j = 0;
    			} break;
    			case 4:
    			{
    				i = 0; j = 1;
    			} break;
    			default:
    			{
    				i = j = 1;
    			} break;
    		}
    		SDL_Rect wallRect = {(xTile + i) * tileWidth, (yTile + j) * tileWidth, tileWidth, tileWidth};
    		int penDx, penDy;
    		computeDistancePenetration(&penDx, &penDy, *xPosWanted, *yPosWanted, wallRect);
    		if ((penDx == 0) && (penDy == 0)) {k += 2;} // Plus de collision avec les nouvelles x/yPosWanted, on passe au prochain bloc
    		else
    		{	// on corrige que selon la plus petite pénétration
    			if(abs(penDx) < abs(penDy))
    			{
    				*xPosWanted -= penDx;
    			} else
    			{
    				*yPosWanted -= penDy;
    			}
    			k += 2; // passage au prochain bloc
    		}
    	}
    }
}

void MoveableObject::computeDistancePenetration(int *penDx, int *penDy, float xPosWanted, float yPosWanted, SDL_Rect wallRect) {
	if((yPos + bounds.h <= wallRect.y) && (wallRect.y < yPosWanted + bounds.h))
	{	// Collision de la face DOWN
		*penDy = (yPosWanted + bounds.h) - wallRect.y;
	}
	else if((yPos >= wallRect.y + wallRect.h) && (wallRect.y + wallRect.h > yPosWanted))
	{	// Collision de la face UP
		*penDy = (wallRect.y + wallRect.h) - yPosWanted;
	}
	if((xPos + bounds.w <= wallRect.x) && (wallRect.x < xPosWanted + bounds.w))
	{	// Collision de la face RIGHT
		*penDx = (xPosWanted + bounds.w) - wallRect.x;
	}
	else if((xPos >= wallRect.x + wallRect.w) && (wallRect.x + wallRect.w > xPosWanted))
	{	// Collision de la face LEFT
		*penDx = (wallRect.x + wallRect.w) - xPosWanted;
	}
}


// accesseurs
int MoveableObject::getId() {return id;}
float MoveableObject::getXPos() {return xPos;}
float MoveableObject::getYPos() {return yPos;}
float MoveableObject::getXSpeed() {return xSpeed;}
float MoveableObject::getYSpeed() {return ySpeed;}
bool MoveableObject::isAlive() {return alive;}

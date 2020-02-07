#include "MoveableObject.h"


// constructeur par defaut
MoveableObject::MoveableObject() {}
// constructeur exhaustif
MoveableObject::MoveableObject(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite) {
	this->alive = true;
	this->xPos = xPos;
	this->yPos = yPos;
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	this->id = id;
	// Doit on faire des new ? Puisqu'en C++ la surcharge d'opérateurs existe, on suppose SDL le fait avec =
	this->bounds = bounds;
	this->sprite = sprite;
}
// destructeur
MoveableObject::~MoveableObject() {}

// methodes
void MoveableObject::move(float dx, float dy) {

}

int MoveableObject::detectMapCollision(float dx, float dy, float xPosWanted, float yPosWanted) {
	int nTiles = GameState::map->mapWidth;
	int tileWidth = GameState::map->tilesWidth;

	int caseCollision = 0; // Aucune collision avec le terrain

    int xTile = (int)(xPosWanted / tileWidth);
    int yTile = (int)(yPosWanted / tileWidth);

    // Collision avec un mur
    if(GameState::map->grid[xTile + nTiles * yTile] == GameState::map->WALL)
    {
    	// pas suffisant
    }



	return caseCollision;
}

// accesseurs
int MoveableObject::getId() {return id;}
float MoveableObject::getXPos() {return xPos;}
float MoveableObject::getYPos() {return yPos;}
float MoveableObject::getXSpeed() {return xSpeed;}
float MoveableObject::getYSpeed() {return ySpeed;}
bool MoveableObject::isAlive() {return alive;}

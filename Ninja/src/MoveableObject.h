#ifndef MOVEABLEOBJECT_H_
#define MOVEABLEOBJECT_H_

#include "GameState.h"


class MoveableObject {

public:
	MoveableObject();
	MoveableObject(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite);
	virtual ~MoveableObject();
	// virtual void fct() = 0 -> methode virtuelle pure ie. doit être implémentée par les instances de la classe fille
	virtual void draw() = 0;
	// methodes
	void move(float dx, float dy);
	int detectMapCollision(float dx, float dy, float xPosWanted, float yPosWanted);
	// accesseurs
	int getId();
	float getXPos();
	float getYPos();
	float getXSpeed();
	float getYSpeed();
	bool isAlive();

private:
    float xPos;
    float yPos;
    float xSpeed;
    float ySpeed;
    bool alive;
    int id;
    SDL_Rect bounds;
    SDL_Texture *sprite;
};


#endif /* MOVEABLEOBJECT_H_ */

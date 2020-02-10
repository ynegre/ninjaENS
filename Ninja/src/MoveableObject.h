#ifndef MOVEABLEOBJECT_H_
#define MOVEABLEOBJECT_H_

#include "SDL/SDL.h"


class MoveableObject {

public:
	MoveableObject();
	MoveableObject(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite);
	virtual ~MoveableObject();
	// virtual void fct() = 0 -> methode virtuelle pure ie. doit être implémentée par les instances de la classe fille
	virtual void draw() = 0;
	// methodes
	void update(float dx, float dy);
	void detectMapCollision(float *xPosWanted, float *yPosWanted);
	void computeDistancePenetration(float *penDx, float *penDy, float xPosWanted, float yPosWanted, SDL_Rect wallRect);
	// accesseurs
	int getId();
	float getXPos();
	float getYPos();
	float getXSpeed();
	float getYSpeed();
	bool isAlive();
    float xSpeed;
    float ySpeed;


protected:
    float xPos;
    float yPos;
    bool alive;
    int id;
    SDL_Rect bounds;
    SDL_Texture *sprite;
};


#endif /* MOVEABLEOBJECT_H_ */

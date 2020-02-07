#ifndef MOVEABLEOBJECT_H_
#define MOVEABLEOBJECT_H_

#include "GameState.h"


class MoveableObject {

public:
	MoveableObject();
	MoveableObject(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite);
	virtual ~MoveableObject();
	// virtual void fct() = 0 -> methode virtuelle pure ie. doit �tre impl�ment�e par les instances de la classe fille
	virtual void draw() = 0;
	// methodes
	void update(float dx, float dy);
	void detectMapCollision(float *xPosWanted, float *yPosWanted);
	void computeDistancePenetration(int *penDx, int *penDy, float xPosWanted, float yPosWanted, SDL_Rect wallRect);
	// accesseurs
	int getId();
	float getXPos();
	float getYPos();
	float getXSpeed();
	float getYSpeed();
	bool isAlive();

protected:
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

#ifndef MOVEABLEOBJECT_H_
#define MOVEABLEOBJECT_H_

#include "SDL/SDL.h"


class MoveableObject {

public:
	MoveableObject();
	MoveableObject(int xPos, int yPos, int xSpeed, int ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite);
	virtual ~MoveableObject();
	// virtual void fct() = 0 -> methode virtuelle pure ie. doit être implémentée par les instances de la classe fille
	virtual void draw() = 0;
	// methodes
	void update(float dx, float dy);
	// accesseurs
	int getId();
	int getXPos();
	int getYPos();
	bool isAlive();

protected:
    int xPos;
    int yPos;
    int xSpeed;
    int ySpeed;
    bool alive;
    int id;
    SDL_Rect bounds;
    SDL_Texture *sprite;
};


#endif /* MOVEABLEOBJECT_H_ */

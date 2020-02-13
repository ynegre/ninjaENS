#ifndef PLAYER_H_
#define PLAYER_H_

#include "MoveableObject.h"

class Player : public MoveableObject {
public:
	Player();
	Player(int xPos, int yPos, int xSpeed, int ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite);
	virtual ~Player();

	void draw();
};

#endif /* PLAYER_H_ */

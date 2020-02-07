#ifndef PLAYER_H_
#define PLAYER_H_

#include "MoveableObject.h"

class Player : public MoveableObject {
public:
	Player();
	Player(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite);
	virtual ~Player();

	void draw();
};

#endif /* PLAYER_H_ */

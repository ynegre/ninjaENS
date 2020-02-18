#ifndef PLAYER_H_
#define PLAYER_H_

#include "MoveableObject.h"

class Player : public MoveableObject {
public:
	Player();
	Player(int xPos, int yPos, int xSpeed, int ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite);
	virtual ~Player();

	void draw();
	int portNumber; // Port associée à la communication bluetooth avec la manette Wii.

};

#endif /* PLAYER_H_ */

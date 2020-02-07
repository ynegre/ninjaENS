#include "Player.h"
#include "SpritesLibrary.h"

Player::Player(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite) : MoveableObject(xPos, yPos, xSpeed, ySpeed, id, bounds, sprite)
{}

Player::Player() {}

Player::~Player() {}

void Player::draw() {
	SDL_Rect dest = {(int)xPos, (int)yPos, 64, 64};
	SpritesLibrary::draw(sprite, NULL, &dest);
}



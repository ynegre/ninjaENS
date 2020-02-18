#include "Player.h"
#include "SpritesLibrary.h"

Player::Player(int xPos, int yPos, int xSpeed, int ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite) : MoveableObject(xPos, yPos, xSpeed, ySpeed, id, bounds, sprite)
{}

Player::Player() {}

Player::~Player() {}

void Player::draw() {
	// -32 car on prend comme centre (xPos,yPos) "fictif" le centre de chaque sprite (64x64) car cela simplifie les calculs.
	SDL_Rect dest = {xPos - 32, yPos - 32, 64, 64};
	SpritesLibrary::draw(sprite, NULL, &dest);
}



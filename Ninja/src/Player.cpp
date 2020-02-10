#include "Player.h"
#include "SpritesLibrary.h"

Player::Player(float xPos, float yPos, float xSpeed, float ySpeed, int id, SDL_Rect bounds, SDL_Texture *sprite) : MoveableObject(xPos, yPos, xSpeed, ySpeed, id, bounds, sprite)
{}

Player::Player() {}

Player::~Player() {}

void Player::draw() {
	// -32 car on prends comme centre (xPos,yPos) "fictif" le centre de chaque sprite (64x64) car cela simplifie les calculs.
	SDL_Rect dest = {(int)xPos - 32, (int)yPos - 32, 64, 64};
	SpritesLibrary::draw(sprite, NULL, &dest);
}



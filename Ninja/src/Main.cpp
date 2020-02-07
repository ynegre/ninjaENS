//============================================================================
// Name        : Ninja
// Author      : Thomas
// Version     :
// Copyright   : Your copyright notice
// Description : Projet Info M2FESUP Intranet
//============================================================================



#include "GameState.h"

int main(int argc, char *argv[]) {

	GameState *game = new GameState();
	game->init("Ninja", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1216, 640);

	const int FPS = 60;
	const int frameDelay = 1000/FPS; // 1000 ms

	Uint32 frameStart;
	int frameTime;

	while (game->isRunning()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart; // temps (ms) écoulé depuis le dernier rendu graphique
		if (frameDelay > frameTime) {SDL_Delay(frameDelay - frameTime);} // Limite le frameRate à 60 FPS

	}
    game->clean();
    return 0;


}

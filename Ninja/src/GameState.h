#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Map.h"

class GameState {

public:
	GameState();
	virtual ~GameState();

	void init(const char *title, int xPos, int yPos, int width, int height);
	void handleEvents();
	void render();
	void update();
	void clean();
	bool isRunning();

	static SDL_Renderer *renderer;
	static Map *map;
	/* Permet d'éviter de créer des références à tout va. En effet, en include "GameState.h",
	 * pas nécessaire de passer GameState::renderer/terrain en parametre des méthodes des autres classes.
	 */

private:
	bool running;
	SDL_Window *window;

	// Methodes qui seront à terme uniquement sur le serveur !
	void moveObjects();
	bool collisionRect(SDL_Rect rectA, SDL_Rect rectB);
	void collisionObjects();


};



#endif /* GAMESTATE_H_ */

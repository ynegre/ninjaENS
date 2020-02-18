#ifndef GAMESTATE_H_
#define GAMESTATE_H_


#include "GestionBluetooth/rs232.h"
#include "Map.h"
#include "Player.h"

class GameState {

public:
	GameState();
	virtual ~GameState();

	void init(const char *title, int xPos, int yPos, int width, int height);
	void initComManetteWii();
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
	Player myPlayer;

	// Commande de position pour myPlayer (celui contrôlé par ce Client du jeu Ninja
	float dx = 0.0;
	float dy = 0.0;
	void updatePosOrderFromBluetooth();


	// Methodes qui seront à terme uniquement sur le serveur !
	bool collisionRect(SDL_Rect rectA, SDL_Rect rectB);
	void collisionObjects();


};



#endif /* GAMESTATE_H_ */

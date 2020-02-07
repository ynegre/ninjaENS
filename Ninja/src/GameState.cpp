#include "GameState.h"
#include "SpritesLibrary.h"
#include <iostream>


/* Definition de nos attributs qui composent notre classe
 * -> poser la question pour cf la différence avec une définition dans le .h en #include "classe.h"
 * correspondante (ce qui risque de faire des appels cycliques de librairie entre elles.
*/
SpritesLibrary spritesLib;
Map* GameState::map = nullptr;
SDL_Renderer* GameState::renderer = nullptr;


GameState::GameState() {}
// destructeur -> on a fait un new avec terrain, on le delete !
GameState::~GameState() {delete map;}



void GameState::init(const char *title, int xPos, int yPos, int width, int height) {

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
    	std::cout << "SDL systems correctly initialized..." << std::endl;

    	window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_SHOWN);
        if(window) {std::cout << "Window created..." << std::endl;}

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {std::cout << "Renderer created..." << std::endl;}
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        spritesLib = SpritesLibrary();
        if(spritesLib.isDownloaded()) {std::cout << "Sprites downloaded..." << std::endl;}

        map = new Map(spritesLib.get(spritesLib.SPRITE_BLOCK_BACK),
        		spritesLib.get(spritesLib.SPRITE_BLOCK),
				spritesLib.get(spritesLib.SPRITE_BONUS));
        if(map->isLoaded()) {std::cout << "Map loaded." << std::endl;}

        SDL_Rect bounds = {-14, 28, -42, 42};
        //Naruto = Player(100, 100, 1.8, 1.8, 0, bounds, spritesLib.get(spritesLib.SPRITE_NARUTO));

        running = true;
    } else {
    	running = false;
    }
};

void GameState::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
	}
};

void GameState::render() {
	SDL_RenderClear(renderer); // clear the current rendering target with the drawing color.

	// insert stuff to render
	map->drawMap();
    static int cnt = 0;
    cnt += 2;

	SDL_Rect dest;
	dest.h = 64;
	dest.w = 64;
	dest.x = cnt;
	dest.y = 0;
	SpritesLibrary::draw(spritesLib.get(spritesLib.SPRITE_NARUTO), NULL, &dest);

    SDL_RenderPresent(renderer);
};

void GameState::update() {
    static int pos = 0;
    // moveObjects
	pos++;
	//std::cout << pos << std::endl;

};

void GameState::moveObjects() {

};

void GameState::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game correctly cleaned." << std::endl;
};

bool GameState::isRunning() {return running;}

bool GameState::collisionRect(SDL_Rect rectA, SDL_Rect rectB) {
    if ((rectB.y >= rectA.y + rectA.h) || (rectA.y >= rectB.y + rectB.h) ||
        (rectB.x >= rectA.x + rectA.w) || (rectA.x >= rectB.x + rectB.w))
    {
        return false; // collision non détectectée
    }
    else
        return true; // collision détectée
}


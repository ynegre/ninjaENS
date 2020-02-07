#ifndef MAP_H_
#define MAP_H_

#include <SDL/SDL.h>

class Map {

public:
	Map();
	Map(SDL_Texture *floorTex, SDL_Texture *wallTex, SDL_Texture *bonusTex);
	virtual ~Map();
	void reloadMap(const char* path);
	void drawMap();
	bool isLoaded();

	enum texture_slot{
		FLOOR,
		WALL,
		BONUS
	};

	static const int tilesWidth = 64;
	static const int mapWidth = 19; // nombre de tiles composant la largeur de la map (x:SDL)
	static const int mapHeight = 10; // nombre de tiles composant la hauteur de la map (y:SDL)

	int grid[mapHeight*mapWidth];// stockage sous format 1D car + rapide d'accès en mémoire (adresse titles se suivent)


private:
	// Textures utilisées pour notre terrain
	SDL_Texture* floor;
	SDL_Texture* wall;
	SDL_Texture* bonus;

	SDL_Rect dest, src;

	bool loaded = false;
};

#endif /* MAP_H_ */

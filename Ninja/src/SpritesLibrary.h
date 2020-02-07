#ifndef SPRITESLIBRARY_H_
#define SPRITESLIBRARY_H_

#include "GameState.h"
#include <string>

class SpritesLibrary {

public:
	SpritesLibrary();
	virtual ~SpritesLibrary();
	void LoadSprites();
	bool isDownloaded();
	SDL_Texture* get(int textureIdx);
	static void draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest);
	// static permet de faire appel à cette méthode sans avoir besoin d'instance de la classe

	enum sprite_slot
	{
	    SPRITE_NARUTO,
	    SPRITE_NARUTO_DEAD,
	    SPRITE_SAKURA,
	    SPRITE_SAKURA_DEAD,
	    SPRITE_SHURIKEN,
	    SPRITE_KUNAI,
	    SPRITE_BLOCK,
	    SPRITE_BLOCK_BACK,
	    SPRITE_NARUTO_WINS,
	    SPRITE_SAKURA_WINS,
		SPRITE_BONUS,
	    NB_SPRITE
	};


private:

	bool correctlyDownloaded = false;
	static const int nbSprites = NB_SPRITE;

	std::string SPRITE_LOAD_PATH[nbSprites] = {
	"bmp\\naruto.bmp",
	"bmp\\naruto_dead.bmp",
	"bmp\\sakura.bmp",
	"bmp\\sakura_dead.bmp",
	"bmp\\shurikens.bmp",
	"bmp\\kunais.bmp",
	"bmp\\block.bmp",
	"bmp\\block_back.bmp",
	"bmp\\Naruto_Wins.bmp",
	"bmp\\Sakura_Wins.bmp",
	"bmp\\bonus.bmp"
	};

	SDL_Texture *textures[nbSprites]; // tableau de nos differentes textures.
	// C'est ce qui a remplacé les SDL_Surface* afin d'afficher nos sprites avec l'outil renderer
};


#endif /* SPRITESLIBRARY_H_ */

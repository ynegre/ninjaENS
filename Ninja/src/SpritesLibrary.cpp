#include "SpritesLibrary.h"


// constructeur par defaut
SpritesLibrary::SpritesLibrary() {LoadSprites();}

SpritesLibrary::~SpritesLibrary() {}


// accesseurs
bool SpritesLibrary::isDownloaded() {return correctlyDownloaded;}

// methodes
SDL_Texture* SpritesLibrary::get(int textureIdx){return textures[textureIdx];}

void SpritesLibrary::draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest) {
	SDL_RenderCopy(GameState::renderer, texture, src, dest);
}

void SpritesLibrary::LoadSprites() {

    for(int i = 0; i < nbSprites; i++)
    {
    	// std::string::c_str() permet de convertir un string en const char*, argument de SDL_LoadBMP !
        SDL_Surface *image = SDL_LoadBMP(SPRITE_LOAD_PATH[i].std::string::c_str());
        // Permet le traitement des pixels mauves (rgb = 255,0,255) comme des pixels transparents !
        Uint32 ColorKey = SDL_MapRGB(image->format, 255, 0, 255);
        SDL_SetColorKey(image, SDL_TRUE, ColorKey);
        textures[i] = SDL_CreateTextureFromSurface(GameState::renderer, image);
    }
    correctlyDownloaded = true;
}

#include "Map.h"
#include "SpritesLibrary.h"
#include <iostream>


Map::Map() {}

Map::Map(SDL_Texture *floorTex, SDL_Texture *wallTex, SDL_Texture *bonusTex) {
	floor = floorTex;
	wall = wallTex;
	bonus = bonusTex;
	reloadMap("bmp\\map.bmp");
	dest = {0,0,64,64}; // x, y, w, h
	src = {0,0,64,64};
}

Map::~Map() {}

void Map::reloadMap(const char* path)
{
    SDL_Surface *dataTerrain = SDL_LoadBMP(path);
    SDL_LockSurface(dataTerrain);

    uint8_t blue, green, red;
    uint32_t color;

    uint8_t *pixelPointer = (uint8_t*)dataTerrain->pixels;
    for(int y = 0; y < mapHeight; y++)
    {
        for(int x = 0; x < mapWidth; x++)
        {
        	/*
        	 * Le format des SDL_Surface->pixels est uint8_t RGB[3] avec le bleu pour LSB.
        	 * Mais attention car le format BMP représente chaque ligne de pixel sur un multiple de 4 octets
        	 * Il complete dans les octets manquant avec des zéros (zeros padding)
        	 * Ici, cela pose probleme car notre terrain fait 19 pixels par ligne -> 19*3 = 57 octets qui sont
        	 * complétés par 3 octets pour arriver à 60 (=15*4) octets.
        	 *  Il faut donc faire en sorte de les sauter !
        	 */
            blue = *pixelPointer++;
            green = *pixelPointer++;
            red = *pixelPointer++;
            color = (red << 16) | (green << 8) | (blue);

            /* Pour le debug, afin d'afficher la memoire ! int cnt; char[50] buffer;
             * std::sprintf(buffer, "cnt : %d, color : %06x, x : %d, y : %d \n", cnt,Color,x,y);
             * std::printf(buffer);
             * cnt++;
             */

            switch(color){
				case 0xFFFFFF: // Floor RGB (blanc)
				{
					grid[x + mapWidth * y] = 0;
				} break;
                case 0x0000FF: // Walls RGB (bleu)
                {
                    grid[x + mapWidth * y] = 1;
                } break;
                case 0xFF0000: // Bonus RGB (rouge)
				{
					grid[x + mapWidth * y] = 2;
				} break;
               default:
                {
                	std::cout << "Problem loading terrain" << std::endl;
                } break;
            }
        }
        if ((mapWidth*3) % 4 != 0) {
        pixelPointer += 4 - (mapWidth*3) % 4; // On saute le padding rajouté par le format .BMP
        }
    }
    SDL_UnlockSurface(dataTerrain);
    SDL_FreeSurface(dataTerrain);
    loaded = true;
}

void Map::drawMap() {

	static int i = 0;
	int type;
    for(int y = 0; y < mapHeight; y++)
    {
        for(int x = 0; x < mapWidth; x++)
        {
        	type = grid[x + mapWidth * y];

        	dest.x = x * tilesWidth;
        	dest.y = y * tilesWidth;
			switch(type){
				case BONUS: // Bonus
				{
					src.x = ((i/4)%8) * tilesWidth; // i/4 afin de réduire la vitesse de rotation
					i++;
					SpritesLibrary::draw(bonus, &src, &dest);
				} break;
                case WALL: // Walls
                {
                	SpritesLibrary::draw(wall, NULL, &dest);
                } break;
                case FLOOR: // Floor
                {
                	SpritesLibrary::draw(floor, NULL, &dest);
                } break;
                default:
                {
                	std::cout << "Problem drawing terrain" << std::endl;
                } break;
			 }
        }
    }
}

bool Map::isLoaded() {return loaded;}


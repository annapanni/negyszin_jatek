#ifndef GRAPHICS_H
#define  GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "linked_list.h"
#include "geometry.h"
#include "map.h"
#include "controls.h"
#include "state.h"
#include "file_management.h"
#include "mytime.h"
#define scWidth 1300
#define scHeight 700

/*az SDL könyvtárhoz tartozó objectek pointerei, melyeket az SDL_init ad vissza*/
typedef struct SDL_pointers{
	SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font *fontSmall;
	TTF_Font *fontLarge;
} SDL_pointers;

/*az SDL könyvtárral kapcsolatos objectek inicializálása
paraméter(ek): -
visszatérési érték: a létrehozott objeckekre mutató pointerek struktúrája*/
SDL_pointers SDL_init();

/*az SDL könyvtárral kapcsolatos objectek felszabadítása
paraméter(ek): felszabadítandó sdl pointerek*/
void SDL_close(SDL_pointers sdl);

/*kirajzolja a teljes képernyőt a state és az objects állapota alapján
paraméter(ek): kirajzoláshoz szükséges sdl pointerek struktúrája, a state és a kirajzolandó objectek
visszatérési érték: -
*/
void drawScreen(SDL_pointers sdl, const State *state, const Objects *objects);

#endif

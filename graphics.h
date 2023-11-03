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

typedef enum textAlign{
	leftAlign = 0,
	centerAlign = 1,
	rightAlign = 2
}textAlign;

typedef struct SDL_pointers{
	SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font *fontSmall;
	TTF_Font *fontLarge;
} SDL_pointers;

SDL_pointers SDL_init();

void drawScreen(SDL_pointers sdl, const State *state, const Objects *objects);

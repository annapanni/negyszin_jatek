#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "linked_list.h"
#include "geometry.h"
#include "map.h"
#include "controls.h"
#include "file_management.h"
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

void drawDelaunay(SDL_Renderer *renderer, const TriLinkedList tris);

void drawEdges(SDL_Renderer *renderer, const EdgeLinkedList edges);

void drawScreen(SDL_pointers sdl, const State *state);

void drawLeaderBoard(SDL_pointers sdl, const State *state, const ResList *top10);

void drawNewGame(SDL_pointers sdl, const State *state);

void drawEndGameWindow(SDL_pointers sdl, const State *state);

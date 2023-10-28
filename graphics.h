#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include "linked_list.h"
#include "geometry.h"
#include "map.h"
#include "controls.h"
#define scWidth 1300
#define scHeight 700

typedef struct SDL_pointers{
	SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font *fontSmall;
	TTF_Font *fontLarge;
} SDL_pointers;

SDL_pointers SDL_init();

void drawDelaunay(SDL_Renderer *renderer, TriLinkedList tris);

void drawEdges(SDL_Renderer *renderer, EdgeLinkedList edges);

void drawScreen(SDL_pointers sdl, State state);

void drawLeaderBoard(SDL_pointers sdl, State state);

void drawNewGame(SDL_pointers sdl, State state);

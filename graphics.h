#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "linked_list.h"
#include "geometry.h"
#include "map.h"
#include "controls.h"
#define scWidth 1300
#define scHeight 700

SDL_Renderer *SDL_init();

void drawDelaunay(SDL_Renderer *renderer, TriLinkedList tris);

void drawEdges(SDL_Renderer *renderer, EdgeLinkedList edges);

void drawScreen(SDL_Renderer *renderer, Vertex *vertice, BtnsList btns, Time t, Palette p);

void drawLeaderBoard(SDL_Renderer *renderer, BtnsList btns, Palette p);

void drawNewGame(SDL_Renderer *renderer, BtnsList btns, Palette p);

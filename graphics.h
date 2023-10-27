#include "linked_list.h"
#include "geometry.h"
#include "map.h"
#define scWidth 1300
#define scHeight 700

SDL_Renderer *SDL_init();

void drawDelaunay(TriLinkedList tris, SDL_Renderer *renderer);

void drawVoronoi(Vertex *vertice, SDL_Renderer *renderer, int offset);

void drawEdges(EdgeLinkedList edges, SDL_Renderer *renderer);

void drawScreen(SDL_Renderer *renderer, Vertex *vertice);

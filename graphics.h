#include "linked_list.h"
#include "geometry.h"
#include "map.h"
#define scWidth 1300
#define scHeight 700

SDL_Renderer *SDL_init();

void drawDelaunay(SDL_Renderer *renderer, TriLinkedList tris);

void drawVoronoi(SDL_Renderer *renderer, Vertex *vertice, int offset);

void drawEdges(SDL_Renderer *renderer, EdgeLinkedList edges);

void drawScreen(SDL_Renderer *renderer, Vertex *vertice);

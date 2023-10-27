#include "linked_list.h"
#include "geometry.h"
#include "map.h"

void drawDelaunay(TriLinkedList tris, SDL_Renderer *renderer);

void drawVoronoi(Vertex *vertice, SDL_Renderer *renderer);

void drawEdges(EdgeLinkedList edges, SDL_Renderer *renderer);

SDL_Renderer *SDL_init();

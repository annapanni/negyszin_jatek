#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include "graphics.h"

void drawDelaunay(TriLinkedList tris, SDL_Renderer *renderer){
	TriChain *c = tris.first;
	while (c != NULL){
		trigonRGBA(renderer, c->tri.a->coord.x, c->tri.a->coord.y,
			c->tri.b->coord.x, c->tri.b->coord.y,
			c->tri.c->coord.x, c->tri.c->coord.y, 255, 0, 0, 255);
		c = c->next;
	}
}

void drawVoronoi(Vertex *vertice, SDL_Renderer *renderer){
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			Point p = {x,y};
			int miniIdx = 0;
			int mindist2 = dist2(vertice[0].coord, p);
			for (int i = 0; i < vertNum; i++) {
				int d = dist2(vertice[i].coord, p);
				if (d<mindist2){
					mindist2 = d;
					miniIdx = i;
				}
			}
			pixelRGBA(renderer, x, y, vertice[miniIdx].col.r, vertice[miniIdx].col.g, vertice[miniIdx].col.b, 200);
		}
	}
}

void drawEdges(EdgeLinkedList edges, SDL_Renderer *renderer){
	EdgeChain *c = edges.first;
	while (c != NULL){
		lineRGBA(renderer, c->e.a->coord.x, c->e.a->coord.y,
			c->e.b->coord.x, c->e.b->coord.y, 0, 255, 0, 255);
		c = c->next;
	}
}
SDL_Renderer *SDL_init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
      exit(1);
  }
  SDL_Window *window = SDL_CreateWindow("Delaunay-Voronoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mapWidth, mapHeight, 0);
  if (window == NULL) {
      SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
      exit(1);
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
      SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
      exit(1);
  }
  SDL_RenderClear(renderer);
	return renderer;
}

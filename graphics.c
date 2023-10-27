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

bool onBorder(Point p, Point a, Point b){
	Point vp = (Point){p.x-a.x, p.y-a.y};
	Point vb = (Point){b.x-a.x, b.y-a.y};
	Point o = (Point){0, 0};
	double cosa = (vp.x*vb.x + vp.y*vb.y) / (sqrt(dist2(o, vp)*dist2(o, vb)));
	double ap = sqrt(dist2(a, p)) * cosa;
	double ab = sqrt(dist2(a, b)) / 2;
	return fabs(ab-ap)<=0.5;
}

void drawVoronoi(Vertex *vertice, SDL_Renderer *renderer){
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			Point p = {x,y};
			double d0 = dist2(vertice[0].coord, p);
			double d1 = dist2(vertice[1].coord, p);
			double mindist2 = d0>d1 ? d1 : d0;
			double min2dist2 = d0>d1 ? d0 : d1;
			int miniIdx = d0>d1 ? 1 : 0;
			int mini2Idx = d0>d1 ? 1 : 0;
			for (int i = 0; i < vertNum; i++) {
				double d = dist2(vertice[i].coord, p);
				if (d<mindist2){
					min2dist2 = mindist2;
					mini2Idx = miniIdx;
					mindist2 = d;
					miniIdx = i;
				} else if (d<min2dist2){
					min2dist2 = d;
					mini2Idx = i;
				}
			}
			Color c;
			Point min1P = vertice[miniIdx].coord;
			Point min2P = vertice[mini2Idx].coord;
			if (onBorder(p, min1P, min2P)){
				c = (Color){255,255,255, 255};
			} else {
				c = vertice[miniIdx].col;
			}
			pixelRGBA(renderer, x, y, c.r, c.g, c.b, c.a);
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
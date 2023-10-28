#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include "graphics.h"

SDL_Renderer *SDL_init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
      exit(1);
  }
  SDL_Window *window = SDL_CreateWindow("Negyszin jatek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scWidth, scHeight, 0);
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

void drawDelaunay(SDL_Renderer *renderer, TriLinkedList tris){
	TriChain *c = tris.first;
	while (c != NULL){
		trigonRGBA(renderer, c->tri.a->coord.x, c->tri.a->coord.y,
			c->tri.b->coord.x, c->tri.b->coord.y,
			c->tri.c->coord.x, c->tri.c->coord.y, 255, 0, 0, 255);
		c = c->next;
	}
}

void drawEdges(SDL_Renderer *renderer, EdgeLinkedList edges){
	EdgeChain *c = edges.first;
	while (c != NULL){
		lineRGBA(renderer, c->e.a->coord.x, c->e.a->coord.y,
			c->e.b->coord.x, c->e.b->coord.y, 0, 255, 0, 255);
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
	return fabs(ab-ap)<=0.6;
}

void drawVoronoi( SDL_Renderer *renderer, Vertex *vertice, Palette pal){
	for (int x = mapOffset; x < mapWidth+mapOffset; x++) {
		for (int y = mapOffset; y < mapHeight+mapOffset; y++) {
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
			SDL_Color c;
			Point min1P = vertice[miniIdx].coord;
			Point min2P = vertice[mini2Idx].coord;
			if (onBorder(p, min1P, min2P)){
				c = pal.border;
			} else {
				c = pal.fields[vertice[miniIdx].col];
			}
			pixelRGBA(renderer, x, y, c.r, c.g, c.b, c.a);
		}
	}
	rectangleRGBA(renderer, mapOffset, mapOffset, mapWidth+mapOffset, mapHeight+mapOffset,
		pal.border.r, pal.border.g, pal.border.b, pal.border.a);
}

void drawWindow(SDL_Renderer *renderer, Palette p){
	boxRGBA(renderer, 200, 100, 1100, 600, p.bckgr.r, p.bckgr.g, p.bckgr.b, p.bckgr.a);
	rectangleRGBA(renderer, 200, 100, 1100, 601, p.border.r, p.border.g, p.border.b, p.border.a);
}

void drawBtn(SDL_Renderer *renderer, Button btn, Palette p){
	switch (btn.type) {
		case text:
			boxRGBA(renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				 p.btn.r, p.btn.g, p.btn.b, p.btn.a);
			break;
		case icon:
			boxRGBA(renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				 p.btn.r, p.btn.g, p.btn.b, p.btn.a);
			break;
		case color:
			boxRGBA(renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				 p.fields[btn.name].r, p.fields[btn.name].g, p.fields[btn.name].b, p.fields[btn.name].a);
			break;
	}

}

void drawLeaderBoard(SDL_Renderer *renderer, State state) {
	drawWindow(renderer, state.palette);
	for (int i = 0; i < btnNum; i++) {
		if (state.btns[i].visibility == leaderboard) {
			drawBtn(renderer, state.btns[i], state.palette);
		}
	}
}

void drawNewGame(SDL_Renderer *renderer, State state) {
	drawWindow(renderer, state.palette);
	for (int i = 0; i < btnNum; i++) {
		if (state.btns[i].visibility == newGame) {
			drawBtn(renderer, state.btns[i], state.palette);
		}
	}
}

void drawScreen(SDL_Renderer *renderer, State state){
	Palette p = state.palette;
	boxRGBA(renderer, 0, 0, scWidth, scHeight, p.bckgr.r, p.bckgr.g, p.bckgr.b, p.bckgr.a);
	drawVoronoi(renderer, state.vertice, p);
	for (int i = 0; i < btnNum; i++) {
		if (state.btns[i].visibility == game) {
			drawBtn(renderer, state.btns[i], p);
		}
	}
	Time t = timeAdd(state.timer, state.timeSincePaused);
	char timestr[10];
	sprintf(timestr, "%.2d:%.2d:%.2d", t.min, t.sec, t.csec);
	stringRGBA(renderer, 1045, 220, timestr, 20, 20, 20, 255);
}

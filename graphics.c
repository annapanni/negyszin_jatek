#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "graphics.h"

SDL_pointers SDL_init(){
	SDL_pointers ps;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
      exit(1);
  }
  ps.window = SDL_CreateWindow("Négyszín játék", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scWidth, scHeight, 0);
  if (ps.window == NULL) {
      SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
      exit(1);
  }
  ps.renderer = SDL_CreateRenderer(ps.window, -1, SDL_RENDERER_SOFTWARE);
  if (ps.renderer == NULL) {
      SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
      exit(1);
  }
	TTF_Init();
	ps.fontSmall = TTF_OpenFont("Improved_Font.ttf", 22);
  if (!ps.fontSmall) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      exit(1);
  }
	ps.fontLarge = TTF_OpenFont("Improved_Font.ttf", 40);
  if (!ps.fontLarge) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      exit(1);
  }

  SDL_RenderClear(ps.renderer);
	return ps;
}

void drawText(SDL_Renderer *renderer, char *text, Point center, TTF_Font *font, SDL_Color col){
	SDL_Surface *text_surf;
	SDL_Texture *text_texture;
	text_surf = TTF_RenderUTF8_Blended(font, text, col);
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surf);
	SDL_Rect position;
	position.x = center.x - text_surf->w / 2;
  position.y = center.y - text_surf->h / 2;
  position.w = text_surf->w;
	position.h = text_surf->h;
  SDL_RenderCopy(renderer, text_texture, NULL, &position);
  SDL_FreeSurface(text_surf);
  SDL_DestroyTexture(text_texture);
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

void drawBtn(SDL_pointers sdl, Button btn, Palette p, int currentColor){
	switch (btn.type) {
		case text:
			boxRGBA(sdl.renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				 p.btn.r, p.btn.g, p.btn.b, p.btn.a);
			char names[][20] = {"Új játék", "Dicsőséglista", "Vissza", "Mehet!"};
			drawText(sdl.renderer, names[btn.name-5],
				(Point){btn.coord.x+btn.width/2, btn.coord.y+btn.height/2} ,
				sdl.fontSmall, p.border);
			break;
		case icon:
			boxRGBA(sdl.renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				 p.btn.r, p.btn.g, p.btn.b, p.btn.a);
			break;
		case color:
			boxRGBA(sdl.renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				p.fields[btn.name].r, p.fields[btn.name].g, p.fields[btn.name].b, p.fields[btn.name].a);
			if (btn.name == currentColor) {
				rectangleRGBA(sdl.renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
					(Sint16)(btn.coord.x+btn.width+1), (Sint16)(btn.coord.y+btn.height+1),
					p.border.r, p.border.g, p.border.b, p.border.a);
			}
			char name[3];
			sprintf(name, "%.1d", btn.name);
			drawText(sdl.renderer, name, (Point){btn.coord.x+btn.width/2, btn.coord.y+btn.height*2}, sdl.fontSmall, p.border);
			break;
	}

}

void drawLeaderBoard(SDL_pointers sdl, State state) {
	drawWindow(sdl.renderer, state.palette);
	for (int i = 0; i < btnNum; i++) {
		if (state.btns[i].visibility == leaderboardMode) {
			drawBtn(sdl, state.btns[i], state.palette, state.currenColor);
		}
	}
}

void drawNewGame(SDL_pointers sdl, State state) {
	drawWindow(sdl.renderer, state.palette);
	for (int i = 0; i < btnNum; i++) {
		if (state.btns[i].visibility == newGameMode) {
			drawBtn(sdl, state.btns[i], state.palette, state.currenColor);
		}
	}
}

void drawScreen(SDL_pointers sdl, State state){
	Palette p = state.palette;
	boxRGBA(sdl.renderer, 0, 0, scWidth, scHeight, p.bckgr.r, p.bckgr.g, p.bckgr.b, p.bckgr.a);
	drawVoronoi(sdl.renderer, state.vertice, p);
	for (int i = 0; i < btnNum; i++) {
		if (state.btns[i].visibility == gameMode) {
			drawBtn(sdl, state.btns[i], p, state.currenColor);
		}
	}
	Time t = timeAdd(state.timer, state.timeSincePaused);
	char timestr[10];
	sprintf(timestr, "%.2d:%.2d:%.2d", t.min, t.sec, t.csec);
	drawText(sdl.renderer, timestr, (Point){1075, 220}, sdl.fontLarge, state.palette.border);
}

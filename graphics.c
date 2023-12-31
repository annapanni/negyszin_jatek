#include "graphics.h"

typedef enum textAlign{
	leftAlign = 0,
	centerAlign = 1,
	rightAlign = 2
}textAlign;

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
	ps.fontSmall = TTF_OpenFont("Handwriting.ttf", 22);
  if (!ps.fontSmall) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      exit(1);
  }
	ps.fontLarge = TTF_OpenFont("Handwriting.ttf", 40);
  if (!ps.fontLarge) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      exit(1);
  }

  SDL_RenderClear(ps.renderer);
	return ps;
}

void SDL_close(SDL_pointers sdl){
	TTF_CloseFont(sdl.fontSmall);
	sdl.fontSmall = NULL;
	TTF_CloseFont(sdl.fontLarge);
	sdl.fontLarge = NULL;
	SDL_DestroyRenderer(sdl.renderer);
  sdl.renderer = NULL;
  SDL_DestroyWindow(sdl.window);
  sdl.window = NULL;

  SDL_Quit();
}

static void drawText(SDL_Renderer *renderer, const char *text, Point center, TTF_Font *font, SDL_Color col, textAlign al){
	SDL_Surface *text_surf;
	SDL_Texture *text_texture;
	text_surf = TTF_RenderUTF8_Blended(font, text, col);
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surf);
	SDL_Rect position;
	position.x = center.x - text_surf->w*al / 2;
  position.y = center.y - text_surf->h*al / 2;
  position.w = text_surf->w;
	position.h = text_surf->h;
  SDL_RenderCopy(renderer, text_texture, NULL, &position);
  SDL_FreeSurface(text_surf);
  SDL_DestroyTexture(text_texture);
}

//for debug purposes, not called
/*
static void drawDelaunay(SDL_Renderer *renderer, const TriLinkedList tris){
	TriChain *c = tris.first;
	while (c != NULL){
		trigonRGBA(renderer, c->tri.a->coord.x, c->tri.a->coord.y,
			c->tri.b->coord.x, c->tri.b->coord.y,
			c->tri.c->coord.x, c->tri.c->coord.y, 255, 0, 0, 255);
		c = c->next;
	}
}
static void drawEdges(SDL_Renderer *renderer, const EdgeLinkedList edges){
	EdgeChain *c = edges.first;
	while (c != NULL){
		lineRGBA(renderer, c->e.a->coord.x+mapOffset, c->e.a->coord.y+mapOffset,
			c->e.b->coord.x+mapOffset, c->e.b->coord.y+mapOffset, 0, 255, 0, 255);
		c = c->next;
	}
}
*/

static int onBorder(Point p, Point a, Point b){
	Point vp = (Point){p.x-a.x, p.y-a.y};
	Point vb = (Point){b.x-a.x, b.y-a.y};
	Point o = (Point){0, 0};
	double cosa = (vp.x*vb.x + vp.y*vb.y) / (sqrt(dist2(o, vp)*dist2(o, vb)));
	double ap = sqrt(dist2(a, p)) * cosa;
	double ab = sqrt(dist2(a, b)) / 2;
	return max2((int)(255*(2.0 - (ab-ap))/2.0), 0);
}

void findClosests(VertList vertice, Point p, int *minIndex1, int *minIndex2){
	double d0 = dist2(vertice.list[0].coord, p);
	double d1 = dist2(vertice.list[1].coord, p);
	double mindist2 = d0>d1 ? d1 : d0;
	double min2dist2 = d0>d1 ? d0 : d1;
	int miniIdx = d0>d1 ? 1 : 0;
	int mini2Idx = d0>d1 ? 0 : 1;
	for (int i = 2; i < vertice.len; i++) {
		double d = dist2(vertice.list[i].coord, p);
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
	*minIndex1 = miniIdx;
	*minIndex2 = mini2Idx;
}

static void drawVoronoi(SDL_Renderer *renderer, VertList vertice, Palette pal){
	SDL_Surface *bmp = SDL_CreateRGBSurface(0, mapWidth, mapHeight, 32, 0, 0, 0, 0);
	for (int y = 0; y < mapHeight; y++) {
		Uint32 *row = (Uint32*) ((char*) bmp->pixels + y*bmp->pitch);
		for (int x = 0; x < mapWidth; x++) {
			Point p = {x,y};
			int miniIdx, mini2Idx;
			findClosests(vertice, p, &miniIdx, &mini2Idx);
			SDL_Color px;
			SDL_Color c = pal.fields[vertice.list[miniIdx].col];
			px.r = c.r;
			px.g = c.g;
			px.b = c.b;
			px.a = c.a;
			//pixelRGBA(renderer, x+mapOffset, y+mapOffset, c.r, c.g, c.b, c.a);
			Point min1P = vertice.list[miniIdx].coord;
			Point min2P = vertice.list[mini2Idx].coord;
			int b_opacity = onBorder(p, min1P, min2P);
			SDL_Color bc = pal.dark;
			px.r = (bc.r * b_opacity + (255 - b_opacity)*px.r)/255;
			px.g = (bc.g * b_opacity + (255 - b_opacity)*px.g)/255;
			px.b = (bc.b * b_opacity + (255 - b_opacity)*px.b)/255;
			//pixelRGBA(renderer, x+mapOffset, y+mapOffset, bc.r, bc.g, bc.b, b_opacity);
			Uint32 col = (px.r >> bmp->format->Rloss << bmp->format->Rshift)
                 | (px.g >> bmp->format->Gloss << bmp->format->Gshift)
                 | (px.b >> bmp->format->Bloss << bmp->format->Bshift);
			row[x] = col;
		}
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bmp);
  SDL_FreeSurface(bmp);
	SDL_Rect dest = {mapOffset, mapOffset, mapWidth, mapHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
	rectangleRGBA(renderer, mapOffset, mapOffset, mapWidth+mapOffset, mapHeight+mapOffset,
		pal.dark.r, pal.dark.g, pal.dark.b, pal.dark.a);
}

static void drawPopup(SDL_Renderer *renderer, Palette p){
	boxRGBA(renderer, 200, 100, 1100, 600, p.bckgr.r, p.bckgr.g, p.bckgr.b, p.bckgr.a);
	rectangleRGBA(renderer, 200, 100, 1100, 601, p.dark.r, p.dark.g, p.dark.b, p.dark.a);
}

static void drawPausedBtn(SDL_Renderer *renderer, Point center, int radius, const State *state, Palette p){
	SDL_Color c = state->diffSett.ironman ? p.grey : p.btn;
	filledCircleRGBA(renderer, center.x, center.y, radius, c.r, c.g, c.b, c.a);
	if (state->paused) {
		c = state->diffSett.ironman ? p.dark : p.pauseArrow;
		filledTrigonRGBA(renderer, center.x + radius*0.5, center.y,
			center.x - radius*0.25, center.y + radius*0.5*(sqrt(3))/2,
			center.x - radius*0.25, center.y - radius*0.5*(sqrt(3))/2,
			c.r, c.g, c.b, c.a);
	} else {
		boxRGBA(renderer, center.x - radius/4, center.y - radius/2.3,
			center.x - radius/8, center.y + radius/2.3,
			p.dark.r, p.dark.g, p.dark.b, p.dark.a);
		boxRGBA(renderer, center.x + radius/4, center.y - radius/2.3,
			center.x + radius/8, center.y + radius/2.3,
			p.dark.r, p.dark.g, p.dark.b, p.dark.a);
	}
}

static void drawBtn(SDL_pointers sdl, Button btn, const State *state, Palette p){
	switch (btn.type) {
		case text:{
			boxRGBA(sdl.renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				p.btn.r, p.btn.g, p.btn.b, p.btn.a);
			char names[][20] = {"Új játék", "Dicsőséglista", "Vissza", "Mehet!", "Könnyű", "Közepes", "Nehéz"};
			drawText(sdl.renderer, names[btn.name-5],
				(Point){btn.coord.x+btn.width/2, btn.coord.y+btn.height/2} ,
				sdl.fontSmall, p.dark, centerAlign);
			break;}
		case icon:
			drawPausedBtn(sdl.renderer, (Point){btn.coord.x+btn.width/2, btn.coord.y+btn.height/2},
			btn.width/2, state, p);
			break;
		case color:{
			boxRGBA(sdl.renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
				(Sint16)(btn.coord.x+btn.width), (Sint16)(btn.coord.y+btn.height),
				p.fields[btn.name].r, p.fields[btn.name].g, p.fields[btn.name].b, p.fields[btn.name].a);
			if (btn.name == state->currentColor) {
				rectangleRGBA(sdl.renderer, (Sint16)btn.coord.x, (Sint16)btn.coord.y,
					(Sint16)(btn.coord.x+btn.width+1), (Sint16)(btn.coord.y+btn.height+1),
					p.dark.r, p.dark.g, p.dark.b, p.dark.a);
			}
			char name[3];
			sprintf(name, "%.1d", btn.name);
			drawText(sdl.renderer, name, (Point){btn.coord.x+btn.width/2, btn.coord.y+btn.height*2}, sdl.fontSmall, p.dark, centerAlign);
			break;}
		case diffRadio:{
			int r = 6;
			char names[][20] = {"Könnyű", "Közepes", "Nehéz"};
			drawText(sdl.renderer, names[btn.name-9], (Point){btn.coord.x+30, btn.coord.y}, sdl.fontSmall, p.dark, leftAlign);
			if (state->diffSett.selectedDiff == btn.name-9) {
				filledCircleRGBA(sdl.renderer, btn.coord.x+r, btn.coord.y+2.5*r, r, p.dark.r, p.dark.g, p.dark.b, p.dark.a);
			} else {
				circleRGBA(sdl.renderer, btn.coord.x+r, btn.coord.y+2.5*r, r, p.dark.r, p.dark.g, p.dark.b, p.dark.a);
			}
			break;}
		case checkBox:{
			int w = 12;
			drawText(sdl.renderer, "Vasember", (Point){btn.coord.x+30, btn.coord.y}, sdl.fontSmall, p.dark, leftAlign);
			if (state->diffSett.selectedIman) {
				boxRGBA(sdl.renderer, btn.coord.x, btn.coord.y+btn.height/2-w, btn.coord.x+w, btn.coord.y+btn.height/2,
					 p.dark.r, p.dark.g, p.dark.b, p.dark.a);
			} else {
				rectangleRGBA(sdl.renderer, btn.coord.x, btn.coord.y+btn.height/2-w, btn.coord.x+w, btn.coord.y+btn.height/2,
					p.dark.r, p.dark.g, p.dark.b, p.dark.a);
			}
			break;}
	}

}

static void drawLeaderBoard(SDL_pointers sdl, const State *state, const Objects *objects) {
	drawPopup(sdl.renderer, objects->palette);
	drawText(sdl.renderer, "Dicsőséglista", (Point){650, 150}, sdl.fontLarge, objects->palette.dark, centerAlign);
	char diffnames[][20] = {"Könnyű", "Közepes", "Nehéz"};
	strcat(diffnames[state->diffSett.difficulty], state->diffSett.ironman ? " - Vasember" : "");
	drawText(sdl.renderer, diffnames[state->diffSett.difficulty], (Point){650, 200}, sdl.fontSmall, objects->palette.dark, centerAlign);
	for (int i = 0; i < objects->btns.len; i++) {
		if (objects->btns.list[i].visibility == leaderboardMode) {
			drawBtn(sdl, objects->btns.list[i], state, objects->palette);
		}
	}
	for (int i = 0; i < objects->top10.len; i++) {
		PlayerResult res = objects->top10.results[i];
		char dispText[46];
		sprintf(dispText, "%2d. %02d:%02d:%02d - %-30s", (i+1)%100, res.t.min%100, res.t.sec%100, res.t.csec%100, res.name);
		drawText(sdl.renderer, dispText, (Point){560, 230+25*i}, sdl.fontSmall, objects->palette.dark, leftAlign);
	}
}

static void drawNewGame(SDL_pointers sdl, const State *state, const Objects *objects) {
	drawPopup(sdl.renderer, objects->palette);
	drawText(sdl.renderer, "Új játék", (Point){650, 150}, sdl.fontLarge, objects->palette.dark, centerAlign);
	drawText(sdl.renderer, "Színezd ki a térképet a színekkel úgy, hogy ne legyen két ugyanolyan színű mező egymás mellett!",
		(Point){650, 190}, sdl.fontSmall, objects->palette.grey, centerAlign);
	for (int i = 0; i < objects->btns.len; i++) {
		if (objects->btns.list[i].visibility == newGameMode) {
			drawBtn(sdl, objects->btns.list[i], state, objects->palette);
		}
	}
	drawText(sdl.renderer, "Név: ", (Point){650,250}, sdl.fontSmall, objects->palette.dark, centerAlign);
	bool cursorOn = SDL_GetTicks()%1000 < 500;
	if (strlen(state->usrnamebuffer)>0) {
		SDL_Color c = strcmp("(névtelen)", state->usrnamebuffer)==0 ? objects->palette.grey : objects->palette.dark;
		drawText(sdl.renderer, state->usrnamebuffer, (Point){650,280}, sdl.fontSmall, c, centerAlign);
	}
	if (cursorOn && (strlen(state->usrnamebuffer)<=0 || strcmp("(névtelen)", state->usrnamebuffer)==0)) {
		drawText(sdl.renderer, "|", (Point){650,280}, sdl.fontSmall, objects->palette.dark, centerAlign);
	}
	drawText(sdl.renderer, "Nehézség: ", (Point){300,340}, sdl.fontSmall, objects->palette.dark, leftAlign);
}

static void drawEndGameWindow(SDL_pointers sdl, const State *state, const Objects *objects){
	drawPopup(sdl.renderer, objects->palette);
	drawText(sdl.renderer, "Gratulálok!", (Point){650, 150}, sdl.fontLarge, objects->palette.dark, centerAlign);
	for (int i = 0; i < objects->btns.len; i++) {
		if (objects->btns.list[i].visibility == endWindowMode) {
			drawBtn(sdl, objects->btns.list[i], state, objects->palette);
		}
	}
	char dispText[15];
	Time tpassed = state->timer.timePassed;
	sprintf(dispText, "Idő: %02d:%02d:%2d", tpassed.min, tpassed.sec, tpassed.csec);
	drawText(sdl.renderer, dispText, (Point){650, 250}, sdl.fontSmall, objects->palette.dark, centerAlign);
	sprintf(dispText, "Helyezés: %d", (objects->userPlace+1)%10000);
	drawText(sdl.renderer, dispText, (Point){650, 290}, sdl.fontSmall, objects->palette.dark, centerAlign);
}

static void drawBackground(SDL_pointers sdl, const State *state, const Objects *objects){
	Palette p = objects->palette;
	boxRGBA(sdl.renderer, 0, 0, scWidth, scHeight, p.bckgr.r, p.bckgr.g, p.bckgr.b, p.bckgr.a);
	drawVoronoi(sdl.renderer, objects->vertice, p);
	for (int i = 0; i < objects->btns.len; i++) {
		if (objects->btns.list[i].visibility == gameMode) {
			drawBtn(sdl, objects->btns.list[i], state, objects->palette);
		}
	}
	Time t = timeAdd(state->timer.timePassed, state->timer.timeSincePaused);
	char timestr[10];
	sprintf(timestr, "%.2d:%.2d:%.2d", t.min, t.sec, t.csec);
	drawText(sdl.renderer, timestr, (Point){1075, 220}, sdl.fontLarge, objects->palette.dark, centerAlign);
}

void drawScreen(SDL_pointers sdl, const State *state, const Objects *objects){
	drawBackground(sdl, state, objects);
	switch (state->mode) {
		case leaderboardMode:
			drawLeaderBoard(sdl, state, objects);
			break;
		case newGameMode:
			drawNewGame(sdl, state, objects);
			break;
		case endWindowMode:
			drawEndGameWindow(sdl, state, objects);
			break;
		default:
			break;
	}
	SDL_RenderPresent(sdl.renderer);
}

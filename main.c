#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "graphics.h"
#include "map.h"
#include "controls.h"
#include "event_handler.h"
#include "debugmalloc.h"

/*feltölti a kapott buttons listát, feltételezi, hogy van elég hely benne*/
void initButtons(Button *buttons){
	buttons[0] = (Button){
		.name = paused,
		.coord = (Point){1040, 250},
		.type = icon,
		.width = 70,
		.height = 70,
		.visibility = gameMode
	};
	buttons[1] = (Button){
		.name = getLeaderboard,
		.coord = (Point){1140, 20},
		.type = text,
		.width = 140,
		.height = 50,
		.visibility = gameMode
	};
	buttons[2] = (Button){
		.name = getNewGame,
		.coord = (Point){1015, 450},
		.type = text,
		.width = 120,
		.height = 60,
		.visibility = gameMode
	};
	buttons[3] = (Button){
		.name = ok,
		.coord = (Point){950, 520},
		.type = text,
		.width = 90,
		.height = 40,
		.visibility = newGameMode
	};
	buttons[4] = (Button){
		.name = back,
		.coord = (Point){260, 520},
		.type = text,
		.width = 90,
		.height = 40,
		.visibility = newGameMode
	};
	buttons[5] = (Button){
		.name = back,
		.coord = (Point){260, 520},
		.type = text,
		.width = 90,
		.height = 40,
		.visibility = leaderboardMode
	};
	buttons[6] = (Button){
		.name = back,
		.coord = (Point){260, 520},
		.type = text,
		.width = 90,
		.height = 40,
		.visibility = endWindowMode
	};
	buttons[7] = (Button){
		.name = color1,
		.coord = (Point){1000, 350},
		.type = color,
		.width = 30,
		.height = 30,
		.visibility = gameMode
	};
	buttons[8] = (Button){
		.name = color2,
		.coord = (Point){1040, 350},
		.type = color,
		.width = 30,
		.height = 30,
		.visibility = gameMode
	};
	buttons[9] = (Button){
		.name = color3,
		.coord = (Point){1080, 350},
		.type = color,
		.width = 30,
		.height = 30,
		.visibility = gameMode
	};
	buttons[10] = (Button){
		.name = color4,
		.coord = (Point){1120, 350},
		.type = color,
		.width = 30,
		.height = 30,
		.visibility = gameMode
	};
}

State startNewGame(State *state){
	genVertice(state->vertice);
	state->paused = true;
	state->ended = false;
	state->mode = gameMode;
	state->timer = (Time){0,0,0};
	state->timeSincePaused = (Time){0,0,0};
	state->timeStarted = SDL_GetTicks();
	state->currentColor = 1;
	state->blankNum = vertNum;
	strcpy(state->username, state->usrnamebuffer);
}

int main(void) {
	//srand(time(NULL));
	SDL_pointers sdl = SDL_init();
	SDL_Renderer *renderer = sdl.renderer;

	State state;
	strcpy(state.usrnamebuffer, "(névtelen)");
	initButtons(state.btns);
	state.palette = (Palette){
		.bckgr = {250, 250, 240, 255},
		.border = {20, 20, 20, 255},
		.btn =  {240, 230, 220, 255},
		.pauseArrow = {16, 196, 70, 255},
		.fields = {
			{248, 252, 252, 255},
			{255, 179, 186, 255},
			{255, 255, 186, 255},
			{186, 255, 201, 255},
			{186, 225, 255, 255},
		}
	};
	startNewGame(&state);

	//event loop
	SDL_Event event;
	do {
		while (!SDL_PollEvent(&event)) {
			if (state.mode == gameMode && !state.ended
				&& state.blankNum == 0 && correctMap(state.vertice)) {
				state.mode = endWindowMode;
				pauseGame(&state);
				state.ended = true;
			}
			if (!state.paused) {
				state.timeSincePaused = timeConvert(SDL_GetTicks() - state.timeStarted);
				moveVertice(state.vertice);
			}
			drawScreen(sdl, state);
			switch (state.mode) {
				case gameMode:
					break;
				case leaderboardMode:
					drawLeaderBoard(sdl, state);
					break;
				case newGameMode:
					drawNewGame(sdl, state);
					break;
				case endWindowMode:
					drawEndGameWindow(sdl, state);
					break;
				case startNewMode:
					startNewGame(&state);
					break;
			}
			SDL_RenderPresent(renderer);
			usleep(1000000/120);
		}
		event_handle(event, &state);
	} while(event.type != SDL_QUIT);

	TTF_CloseFont(sdl.fontSmall);
	TTF_CloseFont(sdl.fontLarge);

	/*
	TriLinkedList triangles = delaunay(vertice);
	EdgeLinkedList edges = finalEdges(triangles);
	drawVoronoi(renderer, vertice);
	drawDelaunay(renderer, triangles);
	drawEdges(renderer, edges);
  SDL_RenderPresent(renderer);

	delTriLinked(&triangles);
	delELinked(&edges);
	*/

	return 0;
}

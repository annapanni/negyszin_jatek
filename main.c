#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "graphics.h"
#include "map.h"
#include "controls.h"
#include "event_handler.h"
#include "file_management.h"
#include "debugmalloc.h"

/*feltölti a kapott buttons listát, feltételezi, hogy van elég hely benne*/
void initButtons(BtnList *btns){
	btns->len = 11;
	Button *buttons = (Button*)malloc(btns->len * sizeof(Button));
	if (buttons == NULL)
		exit(1);
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
	btns->list = buttons;
}

void startNewGame(State *state){
	genVertice(&(state->vertice));
	state->paused = true;
	state->ended = false;
	state->mode = gameMode;
	state->timer = (Timer){
		.timePassed = (Time){0,0,0},
		.timeSincePaused = (Time){0,0,0},
		.timeStarted = SDL_GetTicks()
	};
	state->currentColor = 1;
	state->blankNum = state->vertice.len;
	state->place = -1;
	strcpy(state->username, state->usrnamebuffer);
}

void initialize(State *state){
	strcpy(state->usrnamebuffer, "(névtelen)");
	initButtons(&(state->btns));
	state->palette = (Palette){
		.bckgr = {250, 250, 240, 255},
		.dark = {20, 20, 20, 255},
		.grey = {120, 120, 120, 255},
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
	startNewGame(state);
}

void doMode(SDL_pointers sdl, State *state, ResList *lbTop10){
	drawScreen(sdl, state);
	/*
	TriLinkedList triangles = delaunay(state->vertice);
	EdgeLinkedList edges = finalEdges(triangles);
	drawEdges(sdl.renderer, edges);
	delTriLinked(&triangles);
	delELinked(&edges);
	*/
	switch (state->mode) {
		case gameMode:
			break;
		case leaderboardMode:
			drawLeaderBoard(sdl, state, lbTop10);
			break;
		case newGameMode:
			drawNewGame(sdl, state);
			break;
		case endWindowMode:
			drawEndGameWindow(sdl, state);
			break;
		case startNewMode:
			startNewGame(state);
			break;
		case startLbMode:
			free(lbTop10->results);
			getTop10(lbTop10);
			state->mode = leaderboardMode;
			break;
	}
	SDL_RenderPresent(sdl.renderer);
}

int main(void) {
	srand(time(NULL));
	SDL_pointers sdl = SDL_init();

	State state;
	initialize(&state);
	ResList lbTop10 = {0,NULL};

	//event loop
	SDL_Event event;
	do {
		while (!SDL_PollEvent(&event)) {
			if (state.mode == gameMode && !state.ended
				&& state.blankNum == 0 && correctMap(state.vertice)) {
				pauseGame(&state);
				state.mode = endWindowMode;
				PlayerResult res;
				strcpy(res.name, state.username);
				res.t = state.timer.timePassed;
				state.place = addToLeaderBoard(res);
				state.ended = true;
			}
			if (!state.paused) {
				state.timer.timeSincePaused = timeConvert(SDL_GetTicks() - state.timer.timeStarted);
				moveVertice(state.vertice);
			}
			doMode(sdl, &state, &lbTop10);
			usleep(1000000/120);
		}
		event_handle(event, &state);
	} while(event.type != SDL_QUIT);

	free(lbTop10.results);
	free(state.btns.list);
	free(state.vertice.list);
	TTF_CloseFont(sdl.fontSmall);
	TTF_CloseFont(sdl.fontLarge);
	SDL_Quit();
	return 0;
}

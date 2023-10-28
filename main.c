#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "graphics.h"
#include "map.h"
#include "controls.h"
#include "event_handler.h"

/*feltölti a kapott buttons listát, feltételezi, hogy van elég hely benne*/
void initButtons(Button *buttons){
	buttons[0] = (Button){
		.name = paused,
		.coord = (Point){1040, 250},
		.type = icon,
		.width = 70,
		.height = 70,
		.visibility = game
	};
	buttons[1] = (Button){
		.name = getLeaderboard,
		.coord = (Point){1180, 20},
		.type = text,
		.width = 100,
		.height = 40,
		.visibility = game
	};
	buttons[2] = (Button){
		.name = getNewGame,
		.coord = (Point){1015, 450},
		.type = text,
		.width = 120,
		.height = 40,
		.visibility = game
	};
	buttons[3] = (Button){
		.name = back,
		.coord = (Point){260, 520},
		.type = text,
		.width = 90,
		.height = 40,
		.visibility = leaderboard
	};
	buttons[4] = (Button){
		.name = back,
		.coord = (Point){260, 520},
		.type = text,
		.width = 90,
		.height = 40,
		.visibility = newGame
	};
}

State startNewGame(Vertex *vertice, State *state, Palette p){
	genVertice(vertice);
	state->paused = true;
	state->mode = game;
	state->timer = (Time){0,0,0};
	state->timeSincePaused = (Time){0,0,0};
	state->timeStarted = timeConvert(SDL_GetTicks());
	state->palette = p;
}

int main(void) {
	srand(time(NULL));
	SDL_Renderer *renderer = SDL_init();

	BtnsList buttons;
	buttons.len = 5;
	initButtons(buttons.btns);

	Palette p = {
		.bckgr = {250, 250, 240, 255},
		.border = {20, 20, 20, 255},
		.btn =  {240, 230, 220, 255},
		.fields = {
			{248, 252, 252, 255},
			{255, 0, 255, 255},
			{255, 0, 0, 255},
			{0, 0, 255, 255},
			{0, 255, 0, 255},
		}
	};
	Vertex vertice[vertNum];
	State state;
	startNewGame(vertice, &state, p);

	//event loop
	SDL_Event event;
	do {
		while (!SDL_PollEvent(&event)) {
			if (!state.paused) {
				state.timeSincePaused = timeDiff(timeConvert(SDL_GetTicks()), state.timeStarted);
			}
			drawScreen(renderer, vertice, buttons, timeAdd(state.timer, state.timeSincePaused), state.palette);
			switch (state.mode) {
				case game:
					break;
				case leaderboard:
					drawLeaderBoard(renderer, buttons, state.palette);
					break;
				case newGame:
				drawNewGame(renderer, buttons, state.palette);
					break;
				case end:
					break;
				case endWindow:
					break;
			}
			SDL_RenderPresent(renderer);
			usleep(1000000/120);
		}
		event_handle(event, &state, buttons);
	} while(event.type != SDL_QUIT);

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

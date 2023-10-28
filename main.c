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


int main(void) {
	SDL_Renderer *renderer = SDL_init();

	Vertex vertice[vertNum];
	genVertice(vertice);

	Button buttons[5];
	initButtons(buttons);

	State state = {
		.paused = false,
		.mode = game,
	};

	//event loop
	SDL_Event event;
	do {
		while (!SDL_PollEvent(&event)) {
			if (!paused) {

			}
			drawScreen(renderer, vertice, buttons, 5);
			switch (state.mode) {
				case game:
					break;
				case leaderboard:
					drawLeaderBoard(renderer, buttons, 5);
					break;
				case newGame:
				drawNewGame(renderer, buttons, 5);
					break;
				case end:
					break;
				case endWindow:
					break;
			}
			SDL_RenderPresent(renderer);
			usleep(1000000/120);
		}
		event_handle(event, &state, buttons, 5);
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

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <stdlib.h>
#include "graphics.h"
#include "map.h"
#include "controls.h"

/*feltölti a kapott buttons listát, feltételezi, hogy van elég hely benne*/
void initButtons(Button *buttons){
	buttons[0] = (Button){
		.name = paused,
		.coord = (Point){1040, 300},
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
		.coord = (Point){1015, 400},
		.type = (BtnType)text,
		.width = 120,
		.height = 40,
		.visibility = (Mode)game
	};
}


int main(void) {

	SDL_Renderer *renderer = SDL_init();

	Vertex vertice[vertNum];
	genVertice(vertice);

	Button buttons[3];
	initButtons(buttons);

	//drawing delaunay
	/*
	TriLinkedList triangles = delaunay(vertice);
	EdgeLinkedList edges = finalEdges(triangles);
	drawVoronoi(renderer, vertice);
	drawDelaunay(renderer, triangles);
	drawEdges(renderer, edges);
  SDL_RenderPresent(renderer);
	*/
	drawScreen(renderer, vertice, buttons, 3);
	//wait until closed
  SDL_Event ev;
  while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {}
  SDL_Quit();

	/*
	delTriLinked(&triangles);
	delELinked(&edges);
	*/

	return 0;
}

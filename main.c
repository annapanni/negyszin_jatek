#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <stdlib.h>
#include "graphics.h"
#include "map.h"

int main(void) {

	SDL_Renderer *renderer = SDL_init();

	Vertex vertice[vertNum];
	genVertice(vertice);
	TriLinkedList triangles = delaunay(vertice);
	EdgeLinkedList edges = finalEdges(triangles);

	//drawing delaunay
	/*
	drawVoronoi(vertice, renderer);
	drawDelaunay(triangles, renderer);
	drawEdges(edges, renderer);
  SDL_RenderPresent(renderer);
	*/
	drawScreen(renderer, vertice);
	//wait until closed
  SDL_Event ev;
  while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {}
  SDL_Quit();

	delTriLinked(&triangles);
	delELinked(&edges);

	return 0;
}

#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "graphics.h"
#include "map.h"
#include "controls.h"
#include "state.h"
#include "event_handler.h"
#include "mytime.h"
#include "debugmalloc.h"

/*feltölti a kapott gomblistát az alapértemezett gombokkal
paraméter(ek): egy BtnList pointer, melynek a list mezőjébe egy dinamikusan foglalt memóriaterületre
mutató pointert ír a függvény, ezt a hívónak kell felszabadítani
visszatérési érték: -*/
void initButtons(BtnList *btns){
	btns->len = 15;
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
	buttons[11] = (Button){
		.name = easyDiffBtn,
		.coord = (Point){470, 340},
		.type = diffRadio,
		.width = 90,
		.height = 40,
		.visibility = newGameMode
	};
	buttons[12] = (Button){
		.name = mediumDiffBtn,
		.coord = (Point){630, 340},
		.type = diffRadio,
		.width = 90,
		.height = 40,
		.visibility = newGameMode
	};
	buttons[13] = (Button){
		.name = hardDiffBtn,
		.coord = (Point){780, 340},
		.type = diffRadio,
		.width = 90,
		.height = 40,
		.visibility = newGameMode
	};
	buttons[14] = (Button){
		.name = ironmanBtn,
		.coord = (Point){470, 400},
		.type = checkBox,
		.width = 90,
		.height = 40,
		.visibility = newGameMode
	};
	btns->list = buttons;
}

/*inicializálja a state és objects struktúrákat
paraméter(ek): state és object struktúrára mutató pointer, melynek mezői közül a függvény kitölti
az objects->btns->list és a objects->vertice->list dinamikusan foglalt memóriaterületre
mutató pointer, ezt a hívónak kell felszabadítania
visszatérési érték: -*/
void initialize(State *state, Objects *objects){
	strcpy(state->usrnamebuffer, "(névtelen)");
	state->diffSett.selectedDiff = mediumDiff;
	initButtons(&objects->btns);
	objects->palette = (Palette){
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
	objects->vertice = (VertList){NULL, 0};
	objects->top10 = (ResList){0,NULL};
	startNewGame(state, objects);
}

/*meghívja az inicializáló függvényeket és futtatja az event loopot*/
int main(void) {
	srand(time(NULL));
	SDL_pointers sdl = SDL_init();

	State state;
	Objects objects;
	initialize(&state, &objects);

	//event loop
	SDL_Event event;
	do {
		while (!SDL_PollEvent(&event)) {
			if (!state.paused) {
				state.timer.timeSincePaused = timeConvert(SDL_GetTicks() - state.timer.timeStarted);
				moveVertice(objects.vertice);
			}
			drawScreen(sdl, &state, &objects);
			usleep(1000000/120);
		}
		event_handle(event, &state, &objects);
	} while(event.type != SDL_QUIT);

	free(objects.top10.results);
	free(objects.btns.list);
	free(objects.vertice.list);
	TTF_CloseFont(sdl.fontSmall);
	TTF_CloseFont(sdl.fontLarge);
	SDL_Quit();
	return 0;
}

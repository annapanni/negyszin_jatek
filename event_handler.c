#include <SDL2/SDL.h>
#include <time.h>
#include <stdbool.h>
#include "event_handler.h"

void pauseGame(State *state){
	if (state->paused) {
		state->timeStarted = timeConvert(SDL_GetTicks());
	} else {
		state->timer = timeAdd(state->timeSincePaused, state->timer);
		state->timeSincePaused.min = 0;
		state->timeSincePaused.sec = 0;
		state->timeSincePaused.csec = 0;
	}
	state->paused = !state->paused;
}

void buttonEvent(Button btn, State *state){
	if (btn.type == color) {
		state->currenColor = btn.name;
		return;
	}
	switch (btn.name) {
		case getLeaderboard:
			state->mode = leaderboardMode;
			if (!state->paused)
				pauseGame(state);
			break;
		case getNewGame:
			state->mode = newGameMode;
			if (!state->paused)
				pauseGame(state);
			break;
		case paused:
			pauseGame(state);
			break;
		case back:
			state->mode = gameMode;
			break;
		case ok:
			state->mode = startNewMode;
			break;
	}
}

bool isBtnClicked(Point click, Button btn){
	return  (btn.coord.x <= click.x && click.x <= btn.coord.x + btn.width
		&& btn.coord.y <= click.y && click.y <= btn.coord.y + btn.height);
}

void ifMapClicked(Point click, State *state, int col){
	if (!state->paused && mapOffset <= click.x && click.x <= mapWidth+mapOffset &&
		mapOffset <= click.y && click.y <= mapHeight+mapOffset) {
		state->blankNum += recolorField(click, state->vertice, col);
	}
}

void handleKeys(SDL_Event ev, State *state){
	switch (ev.key.keysym.scancode) {
		case SDL_SCANCODE_SPACE:
			pauseGame(state);
			break;
		case SDL_SCANCODE_1:
			buttonEvent((Button){.name=color1, .type=color}, state);
			break;
		case SDL_SCANCODE_2:
			buttonEvent((Button){.name=color2, .type=color}, state);
			break;
		case SDL_SCANCODE_3:
			buttonEvent((Button){.name=color3, .type=color}, state);
			break;
		case SDL_SCANCODE_4:
			buttonEvent((Button){.name=color4, .type=color}, state);
			break;
	}
}

void handleMouse(SDL_Event ev, State *state){
	Point click = {ev.button.x, ev.button.y};
	switch (ev.button.button) {
		case SDL_BUTTON_LEFT:
			for (int i = 0; i < btnNum; i++) {
				if (state->btns[i].visibility == state->mode && isBtnClicked(click, state->btns[i])) {
					buttonEvent(state->btns[i], state);
				}
			}
			ifMapClicked(click, state, state->currenColor);
			break;
		case SDL_BUTTON_RIGHT:
		ifMapClicked(click, state, 0);
	}
}

void event_handle(SDL_Event ev, State *state){
	Vertex *vertice = state->vertice;
	Button *btns = state->btns;
	switch (ev.type) {
		case SDL_KEYDOWN:
			handleKeys(ev, state);
			break;
		case SDL_MOUSEBUTTONUP:
			handleMouse(ev, state);
			break;
	}
}

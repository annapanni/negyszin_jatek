#include <SDL2/SDL.h>
#include <time.h>
#include <stdbool.h>
#include "event_handler.h"

void pauseGame(State *state){
	if (state->mode == gameMode && !state->ended) {
		if (state->paused) {
			state->timer.timeStarted = SDL_GetTicks();
		} else {
			Timer *trp = &(state->timer);
			trp->timePassed = timeAdd(trp->timeSincePaused, trp->timePassed);
			trp->timeSincePaused.min = 0;
			trp->timeSincePaused.sec = 0;
			trp->timeSincePaused.csec = 0;
		}
		state->paused = !state->paused;
	}
}

void changeCurrentColour(State *state, int code){
	state->currentColor = code;
}

void buttonEvent(Button btn, State *state){
	if (btn.type == color) {
		changeCurrentColour(state, btn.name);
		return;
	}
	switch (btn.name) {
		case getLeaderboard:
			if (!state->paused)
				pauseGame(state);
			state->mode = startLbMode;
			break;
		case getNewGame:
			if (!state->paused)
				pauseGame(state);
			state->mode = newGameMode;
			strcpy(state->usrnamebuffer, state->username);
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
		default:
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
			changeCurrentColour(state, 1);
			break;
		case SDL_SCANCODE_2:
			changeCurrentColour(state, 2);
			break;
		case SDL_SCANCODE_3:
			changeCurrentColour(state, 3);
			break;
		case SDL_SCANCODE_4:
			changeCurrentColour(state, 4);
			break;
		case SDL_SCANCODE_BACKSPACE:
			if (state->mode == newGameMode) {
				delOneChar(state->usrnamebuffer);
			}
			break;
		default:
			break;
	}
}

void handleMouse(SDL_Event ev, State *state){
	Point click = {ev.button.x, ev.button.y};
	switch (ev.button.button) {
		case SDL_BUTTON_LEFT:
			for (int i = 0; i < state->btns.len; i++) {
				if (state->btns.list[i].visibility == state->mode && isBtnClicked(click, state->btns.list[i])) {
					buttonEvent(state->btns.list[i], state);
				}
			}
			ifMapClicked(click, state, state->currentColor);
			break;
		case SDL_BUTTON_RIGHT:
			ifMapClicked(click, state, 0);
			break;
	}
}


void event_handle(SDL_Event ev, State *state){
	switch (ev.type) {
		case SDL_KEYDOWN:
			handleKeys(ev, state);
			break;
		case SDL_MOUSEBUTTONUP:
			handleMouse(ev, state);
			break;
		case SDL_TEXTINPUT:
			if (state->mode == newGameMode) {
				if (strcmp(state->usrnamebuffer, "(névtelen)") != 0) {
					safeCat(state->usrnamebuffer, ev.text.text, 30);
				} else {
					strcpy(state->usrnamebuffer, ev.text.text);
				}
			}
			break;
	}
}

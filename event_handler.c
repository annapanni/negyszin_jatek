#include "event_handler.h"

void startNewGame(State *state, Objects *objects){
	int difficulties[] = {10, 20, 40};
	genVertice(&objects->vertice, difficulties[state->diffSett.selectedDiff]);
	state->paused = true;
	state->ended = false;
	state->mode = gameMode;
	state->timer = (Timer){
		.timePassed = (Time){0,0,0},
		.timeSincePaused = (Time){0,0,0},
		.timeStarted = SDL_GetTicks()
	};
	state->currentColor = 1;
	state->blankNum = objects->vertice.len;
	state->diffSett.difficulty = state->diffSett.selectedDiff;
	state->diffSett.ironman = state->diffSett.selectedIman;
	strcpy(state->username, state->usrnamebuffer);
	objects->userPlace = -1;
}

void pauseGame(State *state){
	if ((state->mode == gameMode || state->mode==endWindowMode) && !state->ended){
		if (state->paused) {
			state->timer.timeStarted = SDL_GetTicks();
			state->paused = false;
		} else if (!state->diffSett.ironman || state->mode==endWindowMode){
			Timer *trp = &state->timer;
			trp->timePassed = timeAdd(trp->timeSincePaused, trp->timePassed);
			trp->timeSincePaused.min = 0;
			trp->timeSincePaused.sec = 0;
			trp->timeSincePaused.csec = 0;
			state->paused = true;
		}
	}
}

void changeCurrentColour(State *state, int code){
	state->currentColor = code;
}

void buttonEvent(Button btn, State *state, Objects *objects){
	if (btn.type == color) {
		changeCurrentColour(state, btn.name);
		return;
	}
	switch (btn.name) {
		case getLeaderboard:
			if (!state->paused)
				pauseGame(state);
			free(objects->top10.results);
			getTop10(&objects->top10, state->diffSett);
			state->mode = leaderboardMode;
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
			startNewGame(state, objects);
			break;
		case easyDiffBtn:
			state->diffSett.selectedDiff = easyDiff;
			break;
		case mediumDiffBtn:
			state->diffSett.selectedDiff = mediumDiff;
			break;
		case hardDiffBtn:
			state->diffSett.selectedDiff = hardDiff;
			break;
		case ironmanBtn:
			state->diffSett.selectedIman = !state->diffSett.selectedIman;
			break;
		default:
			break;
	}
}

bool isBtnClicked(Point click, Button btn){
	return  (btn.coord.x <= click.x && click.x <= btn.coord.x + btn.width
		&& btn.coord.y <= click.y && click.y <= btn.coord.y + btn.height);
}

void ifMapClicked(Point click, State *state, Objects *objects, int col){
	if (!state->paused && state->mode == gameMode && !state->ended
		&& mapOffset <= click.x && click.x <= mapWidth+mapOffset &&
		mapOffset <= click.y && click.y <= mapHeight+mapOffset) {
		state->blankNum += recolorField(click, objects->vertice, col);
		if (state->blankNum == 0 && correctMap(objects->vertice)) {
			state->mode = endWindowMode;
			pauseGame(state);
			PlayerResult res;
			strcpy(res.name, state->username);
			res.t = state->timer.timePassed;
			objects->userPlace = addToLeaderBoard(res, state->diffSett);
			state->ended = true;
		}
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

void handleMouse(SDL_Event ev, State *state, Objects *objects){
	Point click = {ev.button.x, ev.button.y};
	switch (ev.button.button) {
		case SDL_BUTTON_LEFT:
			for (int i = 0; i < objects->btns.len; i++) {
				if (objects->btns.list[i].visibility == state->mode && isBtnClicked(click, objects->btns.list[i])) {
					buttonEvent(objects->btns.list[i], state, objects);
				}
			}
			ifMapClicked(click, state, objects, state->currentColor);
			break;
		case SDL_BUTTON_RIGHT:
			ifMapClicked(click, state, objects, 0);
			break;
	}
}


void event_handle(SDL_Event ev, State *state, Objects *objects){
	switch (ev.type) {
		case SDL_KEYDOWN:
			handleKeys(ev, state);
			break;
		case SDL_MOUSEBUTTONUP:
			handleMouse(ev, state, objects);
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

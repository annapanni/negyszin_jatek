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
			state->mode = leaderboard;
			if (!state->paused)
				pauseGame(state);
			break;
		case getNewGame:
			state->mode = newGame;
			if (!state->paused)
				pauseGame(state);
			break;
		case paused:
			pauseGame(state);
			break;
		case back:
			state->mode = game;
			break;
		case ok:
			printf("newgame\n");
			break;
	}
}

bool isBtnClicked(Point click, Button btn){
	return  (btn.coord.x <= click.x && click.x <= btn.coord.x + btn.width
		&& btn.coord.y <= click.y && click.y <= btn.coord.y + btn.height);
}

void event_handle(SDL_Event ev, State *state, BtnsList btns, Vertex *vertice){
	switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_SPACE:
					pauseGame(state);
					break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			Point click = {ev.button.x, ev.button.y};
			switch (ev.button.button) {
				case SDL_BUTTON_LEFT:
					for (int i = 0; i < btns.len; i++) {
						if (isBtnClicked(click, btns.btns[i])) {
							buttonEvent(btns.btns[i], state);
						}
					}
					if (!state->paused && mapOffset <= click.x && click.x <= mapWidth+mapOffset &&
						mapOffset <= click.y && click.y <= mapHeight+mapOffset) {
						recolorField(click, vertice, state->currenColor);
					}
					break;
			}
			break;
	}
}

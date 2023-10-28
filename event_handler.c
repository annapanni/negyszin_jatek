#include <SDL2/SDL.h>
#include <stdbool.h>
#include "event_handler.h"

void buttonEvent(Button btn, State *state){
	switch (btn.name) {
		case getLeaderboard:
			state->mode = leaderboard;
			break;
		case getNewGame:
			state->mode = newGame;
			break;
		case paused:
			state->paused = !state->paused;
			break;
	}
}

bool isBtnClicked(Point click, Button btn){
	return  (btn.coord.x <= click.x && click.x <= btn.coord.x + btn.width
		&& btn.coord.y <= click.y && click.y <= btn.coord.y + btn.height);
}

void event_handle(SDL_Event ev, State *state, Button *btns, int btnsLen){
	switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_SPACE:
					state->paused = ! state->paused;
					printf("%d\n", state->paused);
					break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			Point click = {ev.button.x, ev.button.y};
			switch (ev.button.button) {
				case SDL_BUTTON_LEFT:
					for (int i = 0; i < btnsLen; i++) {
						if (isBtnClicked(click, btns[i])) {
							buttonEvent(btns[i], state);
						}
					}
					break;
			}
			break;
	}
}

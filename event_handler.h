#include <SDL2/SDL.h>
#include <string.h>
#include "controls.h"
#include "state.h"
#include "map.h"
#include "utilities.h"
#include "mytime.h"
#include "file_management.h"

void startNewGame(State *state, Objects *objects);

void pauseGame(State *state);

void event_handle(SDL_Event ev, State *state, Objects *objects);

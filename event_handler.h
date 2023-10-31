#include <SDL2/SDL.h>
#include <string.h>
#include "controls.h"
#include "map.h"
#include "utilities.h"
#include "mytime.h"

void pauseGame(State *state);

void event_handle(SDL_Event ev, State *state, Objects *objects);

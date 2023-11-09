#ifndef EVENT_HANDLER_H
#define  EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#include "controls.h"
#include "state.h"
#include "map.h"
#include "utilities.h"
#include "mytime.h"
#include "file_management.h"

/*egyes játékok előtti inicializálás
paramétererk: alapállapotba állítandó state és objects
az objects->vertice->list mezőbe egy dinamikusan foglalt memóriaterületre mutató pointer kerül,
ezt a hívónak kell felszabadítania
visszatérési érték: -*/
void startNewGame(State *state, Objects *objects);

/*lekezeli a paraméterként kapoot eseményt
paraméter(ek): az esemény, state és Objects
visszatérési érték: -*/
void event_handle(SDL_Event ev, State *state, Objects *objects);

#endif

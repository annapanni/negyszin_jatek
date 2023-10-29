#ifndef FILE_M_H
#define FILE_M_H

#include <stdio.h>
#include "controls.h"
#include "debugmalloc.h"

typedef struct PlayerResult{
	char name[30+1];
	Time t;
} PlayerResult;

PlayerResult *getTop10();

int addToLeaderBoard(PlayerResult newres);

#endif

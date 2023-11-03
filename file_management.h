#ifndef FILE_M_H
#define FILE_M_H

#include <stdio.h>
#include "mytime.h"
#include "controls.h"
#include "debugmalloc.h"

typedef struct PlayerResult{
	char name[30+1];
	Time t;
} PlayerResult;

typedef struct ResList{
	int len;
	PlayerResult *results;
} ResList;

void getTop10(ResList *list, Difficulty diff);

int addToLeaderBoard(PlayerResult newres, Difficulty diff);

#endif

#include <stdio.h>
#include "controls.h"
#include "debugmalloc.h"

typedef struct Result{
	char name[30];
	Time t;
} Result;

Result *getTop10();

int addToLeaderBoard(Result newres);

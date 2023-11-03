#ifndef STATE_H
#define  STATE_H
#include "controls.h"
#include "file_management.h"

typedef struct State{
	Mode mode;
	bool paused;
	bool ended;
	char username[30+1];
	char usrnamebuffer[30+1];
	Timer timer;
	int currentColor;
	int blankNum;
	DifficultySetting diffSett;
} State;

typedef struct Objects{
	BtnList btns;
	VertList vertice;
	ResList top10;
	int userPlace;
	Palette palette;
} Objects;

#endif

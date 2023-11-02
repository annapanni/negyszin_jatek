#ifndef CONTROLS_H
#define CONTROLS_H
#include <time.h>
#include <stdbool.h>
#include "geometry.h"
#include "file_management.h"
#include "mytime.h"

typedef enum Mode{
	gameMode,
	endWindowMode,
	newGameMode,
	leaderboardMode,
	startNewMode,
	startLbMode
} Mode;

typedef enum BtnName{
	paused = 0,
	color1 = 1,
	color2 = 2,
	color3 = 3,
	color4 = 4,
	getNewGame = 5,
	getLeaderboard = 6,
	back = 7,
	ok = 8
} BtnName;

typedef enum BtnType{
	text,
	color,
	icon
}BtnType;

typedef struct Button{
	BtnName name;
	Point coord;
	BtnType type;
	int width;
	int height;
	Mode visibility;
} Button;

typedef struct BtnList{
	Button *list;
	int len;
} BtnList;

typedef struct Timer {
	Time timePassed;
	Time timeSincePaused;
	int timeStarted;
} Timer;

typedef struct State{
	Mode mode;
	bool paused;
	bool ended;
	char username[30+1];
	char usrnamebuffer[30+1];
	Timer timer;
	int currentColor;
	int blankNum;
} State;

typedef struct Objects{
	BtnList btns;
	VertList vertice;
	ResList top10;
	int userPlace;
	Palette palette;
} Objects;

#endif

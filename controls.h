#ifndef CONTROLS_H
#define CONTROLS_H
#include <time.h>
#include <stdbool.h>
#include "geometry.h"
#include "map.h"
#define btnNum 11

typedef enum Mode{
	gameMode,
	endMode,
	endWindowMode,
	newGameMode,
	leaderboardMode,
	startNewMode
} Mode;

typedef struct Time{
	int min, sec, csec;
} Time;


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

typedef struct State{
	Button btns[btnNum];
	Vertex vertice[vertNum];
	Mode mode;
	bool paused;
	Time timer;
	Time timeSincePaused;
	Time timeStarted;
	Palette palette;
	int currenColor;
	int blankNum;
} State;

Time timeDiff (Time t1, Time t2);

Time timeAdd (Time t1, Time t2);

Time timeConvert(int t1);

#endif

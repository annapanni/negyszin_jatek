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
	paused,
	color1,
	color2,
	color3,
	color4,
	getNewGame,
	getLeaderboard,
	back,
	ok
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
} State;

Time timeDiff (Time t1, Time t2);

Time timeAdd (Time t1, Time t2);

Time timeConvert(int t1);

#endif

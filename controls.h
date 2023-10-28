#ifndef CONTROLS_H
#define CONTROLS_H
#include <time.h>
#include <stdbool.h>
#include "geometry.h"

typedef enum Mode{
	game,
	end,
	endWindow,
	newGame,
	leaderboard
} Mode;

typedef struct Time{
	int min, sec, csec;
} Time;

typedef struct State{
	Mode mode;
	bool paused;
	Time timer;
	Time timeSincePaused;
	Time timeStarted;
} State;

typedef enum BtnName{
	getNewGame,
	getLeaderboard,
	paused,
	color1,
	color2,
	color3,
	color4,
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

typedef struct BtnsList{
	Button btns[5];
	int len;
} BtnsList;

Time timeDiff (Time t1, Time t2);

Time timeAdd (Time t1, Time t2);

Time timeConvert(int t1);

#endif

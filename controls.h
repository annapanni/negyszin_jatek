#ifndef CONTROLS_H
#define CONTROLS_H
#include <time.h>
#include <stdbool.h>
#include "geometry.h"
#include "mytime.h"

typedef enum Mode{
	gameMode,
	endWindowMode,
	newGameMode,
	leaderboardMode
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
	ok = 8,
	easyDiffBtn = 9,
	mediumDiffBtn = 10,
	hardDiffBtn = 11,
	ironmanDiffBtn = 12
} BtnName;

typedef enum BtnType{
	text,
	color,
	icon,
	diffRadio
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

typedef enum Difficulty {
	easyDiff = 0,
	mediumDiff = 1,
	hardDiff = 2,
	ironmanDiff = 3
} Difficulty;

#endif

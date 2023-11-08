#ifndef CONTROLS_H
#define CONTROLS_H

#include <time.h>
#include <stdbool.h>
#include "geometry.h"
#include "mytime.h"

/*a játék lehetséges módjai*/
typedef enum Mode{
	gameMode,
	endWindowMode,
	newGameMode,
	leaderboardMode
} Mode;

/*a gombok nevei, ettől függ, hogy milyen esemény hajtódik végre, illetve, hogy
milyen szöveg, vagy ikon jelenik megnézi
a gombok neveinek számértéket nem szabad megváltoztatni, ezeket a program felhasználja*/
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
	ironmanBtn = 12
} BtnName;

/*gombok megjelenésének/funkcióinak típusa*/
typedef enum BtnType{
	text,
	color,
	icon,
	diffRadio,
	checkBox
}BtnType;

/*gomb struktúra*/
typedef struct Button{
	BtnName name;
	Point coord;
	BtnType type;
	int width;
	int height;
	Mode visibility;
} Button;

/*gombok listája*/
typedef struct BtnList{
	Button *list;
	int len;
} BtnList;

/*időzítő struktúra*/
typedef struct Timer {
	Time timePassed;
	Time timeSincePaused;
	int timeStarted;
} Timer;

/*a játék lehetséges nehézségi módjai, a számértékeket a program felhasználja*/
typedef enum Difficulty {
	easyDiff = 0,
	mediumDiff = 1,
	hardDiff = 2
} Difficulty;

/*a játék nehézségi módjának beállítása*/
typedef struct DifficultySetting{
	Difficulty difficulty;
	Difficulty selectedDiff;
	bool ironman;
	bool selectedIman;
} DifficultySetting;

#endif

#ifndef CONTROLS_H
#define CONTROLS_H
#include <stdbool.h>
#include "geometry.h"

typedef enum Mode{
	game,
	end,
	endWindow,
	newGame,
	leaderboard
} Mode;

typedef struct State{
	Mode mode;
	bool paused;
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


#endif

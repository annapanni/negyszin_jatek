#ifndef MYTIME_H
#define  MYTIME_H

typedef struct Time{
	int min, sec, csec;
} Time;

Time timeAdd (Time t1, Time t2);

Time timeConvert(int t1);

int compTime(Time t1, Time t2);

#endif

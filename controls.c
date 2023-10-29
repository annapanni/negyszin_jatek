#include "controls.h"

Time timeAdd (Time t1, Time t2){
	Time newTime;
	newTime.csec = t1.csec + t2.csec;
	newTime.sec = t1.sec + t2.sec + newTime.csec/100;
	newTime.min = t1.min + t2.min + newTime.sec/60;
	newTime.csec = newTime.csec%100;
	newTime.sec = newTime.sec%60;
	return newTime;
}

Time timeConvert(int t1){
	Time newTime;
	newTime.csec = (t1/10)%100;
	newTime.sec = (t1/1000)%60;
	newTime.min = t1/60000;
	return newTime;
}

int compTime(Time t1, Time t2){
	if (t1.min < t2.min || (t1.min==t2.min && t1.sec < t2.sec)
		|| (t1.min==t2.min && t1.sec==t2.sec && t1.csec < t2.csec))
		return -1;
	if (t1.min > t2.min || (t1.min==t2.min && t1.sec > t2.sec)
		|| (t1.min==t2.min && t1.sec==t2.sec && t1.csec > t2.csec))
		return 1;
	return 0;
}

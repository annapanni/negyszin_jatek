#include "controls.h"

Time timeDiff (Time t1, Time t2){
	Time newTime;
	newTime.csec = t1.csec - t2.csec;
	int negModifier = newTime.csec > 0 ? 0 : newTime.csec/100 +1;
	newTime.sec = t1.sec - t2.sec + (newTime.csec+100*negModifier)/100 -negModifier;
	newTime.csec = (newTime.csec+100*negModifier)%100;
	negModifier = newTime.sec > 0 ? 0 : newTime.sec/60 +1;
	newTime.min = t1.min - t2.min + (newTime.sec+60*negModifier)/60 -negModifier;
	newTime.sec = (newTime.sec+60*negModifier)%60;
	return newTime;
}

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
	newTime.min = t1/600000;
	return newTime;
}

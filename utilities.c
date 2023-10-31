#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "utilities.h"

int randint(int a, int b){
	return (rand()%(b-a)+a);
}
double randDouble(double a, double b, int precision){
	int r = rand();
	double m = r%(int)((a-b)*pow(10, precision)) / pow(10, precision);
	return m + a;
}
int min2(int a, int b){
	return a<b ? a : b;
}

int max2(int a, int b){
	return a>b ? a : b;
}

void safeCat(char *str1, const char *str2, int maxlen){
	if (strlen(str1)+strlen(str2) <= maxlen) {
		strcat(str1,str2);
	}
}

void delOneChar(char *str){
	int textlen = strlen(str);
  do {
    if (textlen == 0)
        break;
    if ((str[textlen-1] & 0x80) == 0x00)   {
        str[textlen-1] = 0x00;
        break;
    }
    if ((str[textlen-1] & 0xC0) == 0x80) {
        str[textlen-1] = 0x00;
        textlen--;
    }
    if ((str[textlen-1] & 0xC0) == 0xC0) {
        str[textlen-1] = 0x00;
        break;
    }
  } while(true);
}

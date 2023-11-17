#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/*visszad egy egész értéket [a,b) intervallumból*/
int randInt(int a, int b);
/*visszad egy valós értéket [a,b) intervallumból adott pontossággal*/
double randDouble(double a, double b, int precision);
/*két egész közül visszaadja a kisebbet*/
int min2(int a, int b);
/*két egész közül visszaadja a nagyobbat*/
int max2(int a, int b);
/*ha az összefűzött sztring hossza nem haladja meg a paraméterként kapott maxlent,
hozzáfűzi az elsőhöz a másodikat, különben nem csinál semmit*/
void safeCat(char *str1, const char *str2, int maxlen);
/*a többites karakterek törlésére szolgál, mindig pontosan a legutolsó karaktert törli egy sztringből*/
void delOneChar(char *str);

#endif

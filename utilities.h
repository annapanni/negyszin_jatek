#ifndef UTIL_H
#define UTIL_H

/*visszad egy egész értéket [a,b) intervallumból*/
int randint(int a, int b);
/*visszad egy valós értéket [a,b) intervallumból adott pontossággal*/
double randDouble(double a, double b, int precision);
/*két egész közül visszaadja a kisebbet*/
int min2(int a, int b);


#endif
#ifndef MYTIME_H
#define  MYTIME_H

/*egyéni idő adatstruktúra*/
typedef struct Time{
	int min, sec, csec;
} Time;

/*összead két időértéket
paraméter(ek): összeadandó idő struktúrák
visszatérési érték: időstruktúrák összege*/
Time timeAdd (Time t1, Time t2);

/*milisekundumot átkonzvertálja az egényi időstrukúrára
paraméter(ek): konvertálandó idő milisekundumban
visszatérési érték: konvertált időstruktúra*/
Time timeConvert(int t1);

/*összehasonlít két időértéket
paraméter(ek): összahasonlítandó idő struktúrák
visszatérési érték: -1, 0, 1
-1 ha  t1 < t2
0 ha egyenlőek
1 ha t1 > t2*/
int compTime(Time t1, Time t2);

#endif

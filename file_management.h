#ifndef FILE_M_H
#define FILE_M_H

#include <stdio.h>
#include "mytime.h"
#include "controls.h"
#include "debugmalloc.h"

/*egy játkékos által elért eredményt tároló struktúra*/
typedef struct PlayerResult{
	char name[30+1];
	Time t;
} PlayerResult;

/*játékosok eredményeit eltároló lista*/
typedef struct ResList{
	int len;
	PlayerResult *results;
} ResList;

/*kiolvasssa a nehézségnek megfelelő fájlból az első tíz legjobb játékos eredményeit
paraméter(ek): erdemények listája, melynek list mezőjébe egy dinamikusan foglalt
memóriaterületre muató pointer kerül, ezt a hívónak kell felszabadítania
diff: a jelenlegi nehézségi szint, ami alapján ki tudja választani a megfelelő fájlt
visszatérési érték: -*/
void getTop10(ResList *list, DifficultySetting diff);

/*hozzáad egy új eredményt a megfelelő fájlban lévő dicsőséglistához
paraméter(ek): az új eredmény, melyet a megfelelő helyre ír be a megfelelő fájlba
diff: a jelenlegi nehézségi szint, ami alapján ki tudja választani a megfelelő fájlt
visszatérési érték: a paraméterként megkaptt eredményt helyezése az adott nehézségi kategóriában*/
int addToLeaderBoard(PlayerResult newres, DifficultySetting diff);

#endif

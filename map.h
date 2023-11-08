#ifndef MAP_H
#define MAP_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif
#define mapWidth 800
#define mapHeight 600
#define mapOffset 50
#include "geometry.h"
#include "linked_list.h"
#include "utilities.h"
#include "debugmalloc.h"

/*létrehozza a vertexek tömbjét 4 fix sarokponttal és random genrált elemekkel
paraméter(ek): VertList pointer, melynek a list mezőjébe egy dinamikusan foglalt memóriaterületre
mutató pointer íródik, ezt a hívónak kell felszabadítania
vertNum: a generálandó pontok száma, minimum négynek kell lennie, mivel 4 fix sarokpont mindig van
visszatérési érték: -
*/
void genVertice(VertList *vertice, int vertNum);

/*létrehozza a delaunay triangulácíót egy láncolt listába
paraméter(ek): vertexek listája, ami alapján a triangulácíót generáljuk
visszatérési érték: a listára mutató pointer struct -hívónak kell felszabadítania*/
//csak debughoz kell, a grpahics-ban a drawdelaunay használja map.c-n kívül
TriLinkedList delaunay(VertList vertice);

/*elkészíti a a végső szomszédsági gráfot, tehát megnézi, hogy a mezők valójában
csak a térképen kívűl, vagy valóban érintkeznek-e
paraméter(ek): triangulácíó, ami alapján elkészíti a végleges éleket
visszatérési érték: a listára mutató pointer struct -hívónak kell felszabadítania*/
//csak debughoz kell, a grpahics használja map.c-n kívül
EdgeLinkedList finalEdges(TriLinkedList triangles);

/*elmozgatja a pontokat a megadott sebességük alapján és random változatat az irányukon
paraméter(ek): az elmozgatandó vertexek listája
visszatérési érték: -
*/
void moveVertice(VertList vertice);

/*átálltja annak a mezőnek a színét, ami az adott koordinátájú pontot tartalmazza
paraméter(ek): a koordináta, amelyhez tartozó mezőt át kell színezni
a mezőkhöz tartozó vertexek listája
a színm amire át akarjuk állítani a mezőt
visszatérési érték: -1, 0 vagy 1
-1 ha a mezőt semleges színről egy nem semlegesre lett színezve
0 ha a mezőt semlegesről semlegesre, vagy nem semlegesről nem semlegesre lett színezve
1 ha a mezőt nem semlegesről semglegesre lett színezve
*/
int recolorField(Point click, VertList vertice, int col);

/*megnézi hogy a térkép kiszínezése helyes-e, azaz nincs két egmyás melletti ugyanolyan színű mező
paraméter(ek): ellenőrizendő vertexek listája
visszatérési érték: true ha a színezés helyes, false ha nem
*/
bool correctMap(const VertList vertice);

#endif

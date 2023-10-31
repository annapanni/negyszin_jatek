#ifndef MAP_H
#define MAP_H
#define mapWidth 800
#define mapHeight 600
#define mapOffset 50
#include "geometry.h"
#include "linked_list.h"
#include "utilities.h"
#include "debugmalloc.h"

/*kitölti a paraméterként megkapott vertice tömböt, összesen vertNum elemmel*/
void genVertice(VertList *verticem, int vertNum);

/*létrehozza a delaunay triangulácíót egy láncolt listába, amit a hívónak kell
felszabadítania (a visszatérési értéke a listára mutató pointer struct)*/
TriLinkedList delaunay(VertList vertice);

/*elkészíti a a végső szomszédsági gráfot, tehát megnézi, hogy a mezők valójában
csak a térképen kívűl, vagy valóban érintkeznek-e*/
EdgeLinkedList finalEdges(TriLinkedList triangles);

void moveVertice(VertList vertice);

int recolorField(Point click, VertList vertice, int col);

bool correctMap(VertList vertice);

#endif

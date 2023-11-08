#ifndef LINKED_H
#define LINKED_H

#include <stdlib.h>
#include "geometry.h"

/*VertTri láncolt lista típus*/
typedef struct TriChain{
	VertTri tri;
	struct TriChain *next;
} TriChain;
/*egy láncolt lista adatait tárolja*/
typedef struct TriLinkedList{
	TriChain *first;
	TriChain *last;
	int len;
} TriLinkedList;
/*VertEdge láncolt lista típus*/
typedef struct EdgeChain{
	VertEdge e;
	struct EdgeChain *next;
} EdgeChain;
/*egy láncolt lista adatait tárolja*/
typedef struct EdgeLinkedList{
	EdgeChain *first;
	EdgeChain *last;
	int len;
} EdgeLinkedList;

/*hozzáadja az elemet a láncolt listához
paraméter(ek): a módosítandó lista, és az új elem
visszatérési érték: - */
void addToTriLinked(TriLinkedList *list, VertTri new);

/*kivágja az adott elemet a láncolt listából
paraméter(ek): a módosítandó lista, és a törlendő elemre mutató pointer
visszatérési érték: - */
void rmvfromTriLinked(TriLinkedList *list, TriChain *tormv);

/*letörli a láncolt listát, felszabadítva a memóriát
paraméter(ek): a módosítandó lista, törlés után pointereit NULLra állítja
visszatérési érték: -*/
void delTriLinked(TriLinkedList *list);

/*hozzáadja az elemet a láncolt listához
paraméter(ek): a módosítandó lista, és az új elem
visszatérési érték: - */
void addToELinked(EdgeLinkedList *list, VertEdge new);

/*kivágja az adott elemet a láncolt listából
paraméter(ek): a módosítandó lista, és a törlendő elemre mutató pointer
visszatérési érték: - */
void rmvfromELinked(EdgeLinkedList *list, EdgeChain *tormv);

/*letörli a láncolt listát, felszabadítva a memóriát
paraméter(ek): a módosítandó lista, törlés után pointereit NULLra állítja
visszatérési érték: -*/
void delELinked(EdgeLinkedList *list);

#endif

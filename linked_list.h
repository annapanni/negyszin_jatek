#ifndef LINKED_H
#define LINKED_H

#include "geometry.h"

/*VertTri láncsolt lista típus*/
typedef struct TriChain{
	VertTri tri;
	struct TriChain *next;
} TriChain;
/*egy láncsolt lista adatait tárolja*/
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
/*egy láncsolt lista adatait tárolja*/
typedef struct EdgeLinkedList{
	EdgeChain *first;
	EdgeChain *last;
	int len;
} EdgeLinkedList;

/*hozzáadja az elemet a láncolt listához*/
void addToTriLinked(TriLinkedList *list, VertTri new);
/*kivágja az adott elemet a láncolt listából*/
void rmvfromTriLinked(TriLinkedList *list, TriChain *tormv);
/*letörli a láncolt listát, felszabadítva a memóriát, a paraméterként kapott
struct pointereit NULLra állítja*/
void delTriLinked(TriLinkedList *list);
/*hozzáadja az elemet a láncolt listához*/
void addToELinked(EdgeLinkedList *list, VertEdge new);
/*kivágja az elemet a láncolt listából*/
void rmvfromELinked(EdgeLinkedList *list, EdgeChain *tormv);
/*letörli a láncolt listát, felszabadítva a memóriát, a paraméterként kapott
struct pointereit NULLra állítja*/
void delELinked(EdgeLinkedList *list);

#endif

#include <stdlib.h>
#include "linked_list.h"

/*hozzáadja az elemet a láncolt listához*/
void addToTriLinked(TriLinkedList *list, VertTri new){
	list->len++;
	TriChain *newChain = (TriChain*)malloc(sizeof(TriChain));
	newChain->tri = new;
	newChain->next = NULL;
	if (list->last == NULL) {
		list->first = newChain;
		list->last = newChain;
		return;
	}
	list->last->next = newChain;
	list->last = newChain;
}
/*kivágja az adott elemet a láncolt listából*/
void rmvfromTriLinked(TriLinkedList *list, TriChain *tormv){
	list->len--;
	if (list->first == tormv) {
		TriChain *newFirst = list->first->next;
		free(list->first);
		list->first = newFirst;
		if (list->first == NULL) {//ő volt az utolsó elem a listában
			list->last = NULL;
		}
		tormv = NULL;
		return;
	}
	TriChain *prev = list->first;
	TriChain *current =  list->first->next;
	while (current != NULL) {
		if (current == tormv) {
			prev->next = current->next;
			free(current);
			if (prev->next == NULL) {//utolsót szedtük ki
				list->last = prev;
			}
			tormv = NULL;
			return;
		}
		prev = current;
		current = prev->next;
	}
}
/*letörli a láncolt listát, felszabadítva a memóriát, a paraméterként kapott
struct pointereit NULLra állítja*/
void delTriLinked(TriLinkedList *list){
	TriChain *current =  list->first;
	while (current != NULL) {
		TriChain *next = current->next;
		free(current);
		current = next;
	}
	list->first = NULL;
	list->last = NULL;
	list->len = 0;
}

/*hozzáadja az elemet a láncolt listához*/
void addToELinked(EdgeLinkedList *list, VertEdge new){
	list->len++;
	EdgeChain *newChain = (EdgeChain*)malloc(sizeof(EdgeChain));
	newChain->e = new;
	newChain->next = NULL;
	if (list->last == NULL) {
		list->first = newChain;
		list->last = newChain;
		return;
	}
	list->last->next = newChain;
	list->last = newChain;
}
/*kivágja az elemet a láncolt listából*/
void rmvfromELinked(EdgeLinkedList *list, EdgeChain *tormv){
	list->len--;
	if (list->first == tormv) {
		EdgeChain *newFirst = list->first->next;
		free(list->first);
		list->first = newFirst;
		tormv = NULL;
		return;
	}
	EdgeChain *prev;
	EdgeChain *current =  list->first;
	while (current != NULL) {
		if (current == tormv) {
			prev->next = current->next;
			free(current);
			tormv = NULL;
			return;
		}
		prev = current;
		current = prev->next;
	}
}
/*letörli a láncolt listát, felszabadítva a memóriát, a paraméterként kapott
struct pointereit NULLra állítja*/
void delELinked(EdgeLinkedList *list){
	EdgeChain *current =  list->first;
	while (current != NULL) {
		EdgeChain *next = current->next;
		free(current);
		current = next;
	}
	list->first = NULL;
	list->last = NULL;
	list->len = 0;
}

/* for debugging
void printAll(TriLinkedList *list){
	TriChain *c = list->first;
	printf("%d -", list->len);
	int n = 0;
	while (c != NULL){
		printf("(%g, %g) ", c->tri.a->coord.x, c->tri.b->coord.x);
		c = c->next;
		n++;
	}
	printf("\n");
	assert (n == list->len);
}
*/

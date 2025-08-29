#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "List.h"
int main(void){
	Node* a = newNode(1);
	Node* b = newNode(2);
	Node* c = newNode(3);

	a->next = b;
	b->next = c;
	c->next = NULL;
	a->prev = NULL;
	c->prev = b;
	b->prev = a;
	List* L = newList();
	L->front = a;
	L->back=c;
	L->length = 3;
	moveFront(L);
	L->index = 0;
	printf("%d\n",getIndex(L));
	printf("%d\n",getLength(L));
	printf("%d\n",getFront(L));	
	printf("%d\n",getBack(L));
	printf("next\n");
	for (int i = 0; i < 6; i++){
		printf("E");
		printf("%d: %d,\n", getIndex(L),getCursor(L));
		moveNext(L);
		
	}
	printf("prvev\n");
	moveBack(L);
	for (int i = 0; i < 6; i++){
		printf("E");
		printf("%d: %d,\n", getIndex(L),getCursor(L));
		movePrev(L);
		
	}		

	return 0;
}

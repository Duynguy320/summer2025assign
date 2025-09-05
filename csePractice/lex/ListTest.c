#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "List.h"
int main(void){
	Node* a = newNode(1);
	Node* b = newNode(8);
	Node* c = newNode(9);

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
	
		
	printf("thnigy1 %d: %d,\n", getIndex(L),getCursor(L));	
	
	moveFront(L);
	printf("thnigy2 %d: %d,\n", getIndex(L),getCursor(L));	
	moveNext(L);
	printf("start og thing \n");
	 
	printf("thnig2y %d: %d,\n", getIndex(L),getCursor(L));	
	insertBefore(L,2);
	printf("thing3y %d: %d,\n", getIndex(L),getCursor(L));
	insertBefore(L,3);
	printf("thi4y %d: %d,\n", getIndex(L),getCursor(L));
	insertBefore(L,4);
	printf("thing5y %d: %d,\n", getIndex(L),getCursor(L));
	insertBefore(L,5);
		printf("thing6y %d: %d,\n", getIndex(L),getCursor(L));
	insertBefore(L,6);
		printf("thing7y %d: %d,\n", getIndex(L),getCursor(L));
	insertBefore(L,7);
	    prepend(L, 10);
    append(L, 20);
    append(L, 30);
    	moveBack(L);
	movePrev(L);
	movePrev(L);
	insertAfter(L,69);
	moveFront(L);	
	for (int i = 0; i < getLength(L); i++){
		printf("Index ");
		printf("%d: %d,\n", getIndex(L),getCursor(L));
		moveNext(L);
		
	}	

	return 0;
}

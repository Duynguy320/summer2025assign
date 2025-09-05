#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main(void) {
        int* x1 = malloc(sizeof(int));
        int* x2 = malloc(sizeof(int));
        int* x3 = malloc(sizeof(int));
        *x1 = 10; *x2 = 20; *x3 = 30;

        Node* a = newNode(x1);
        Node* b = newNode(x2);
        Node* c = newNode(x3);

        a->next = b;
        b->next = c;
        c->next = NULL;
        a->prev = NULL;
        c->prev = b;
        b->prev = a;

        List* L = newList();
        L->front = a;
        L->back = c;
        L->length = 3;

        moveFront(L);
        printf("%d\n", getIndex(L));
        printf("%d\n", getLength(L));
        printf("%d\n", *(int*)getFront(L));
        printf("%d\n", *(int*)getBack(L));

        for (int i = 0; i < getLength(L); i++) {
        	void* cur = getCursor(L);
                if (cur) printf("%d\n", *(int*)cur);
                moveNext(L);
        }

        moveBack(L);
        printf("%d\n", *(int*)getCursor(L));
	
	int* array = malloc(5 * sizeof(int));
	for (int i = 0; i < 5; i++) {
                array[i] = i + 1;
        }
	Node* nums = newNode(array);

        freeList(L);
        return 0;
}


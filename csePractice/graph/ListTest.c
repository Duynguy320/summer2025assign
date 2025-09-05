#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "List.h"

int main(void){
    int *x1 = malloc(sizeof(int));
    int *x2 = malloc(sizeof(int));
    int *x3 = malloc(sizeof(int));
    *x1 = 1;
    *x2 = 2;
    *x3 = 3;

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
    L->index = 0;

    printf("%d\n",getIndex(L));
    printf("%d\n",getLength(L));
    printf("%d\n",*(int*)getFront(L));
    printf("%d\n",*(int*)getBack(L));
    printf("next\n");
    for (int i = 0; i < 6; i++){
        printf("E");
        void* cur = getCursor(L);
        if (cur) printf("%d: %d,\n", getIndex(L),*(int*)cur);
        else printf("%d: (null),\n", getIndex(L));
        moveNext(L);
    }
    printf("prvev\n");
    moveBack(L);
    for (int i = 0; i < 6; i++){
        printf("E");
        void* cur = getCursor(L);
        if (cur) printf("%d: %d,\n", getIndex(L),*(int*)cur);
        else printf("%d: (null),\n", getIndex(L));
        movePrev(L);
    }

    return 0;
}


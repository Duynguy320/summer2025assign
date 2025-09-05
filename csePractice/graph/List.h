#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

#ifndef LIST_C
#define LIST_C

// Constructors-Destructors ---------------------------------------------------
Node *newNode(void* data){
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "malloc for node failed\n");
        exit(1);
    }
    new_node->data = data;   // store void*
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void freeNode(Node* node){
    if (node) free(node);
}

List* newList(void){
    List* L = malloc(sizeof(List));
    if (!L) {
        fprintf(stderr, "malloc for list failed\n");
        exit(1);
    }
    L->length = 0;
    L->index = -1;
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    return L;
}

void freeList(List* L){
    if (!L) return;
    Node* cur = L->front;
    while (cur) {
        Node* next = cur->next;
        freeNode(cur);
        cur = next;
    }
    free(L);
}

// Access functions -----------------------------------------------------------
int getLength(List* L) {
    return L->length;
}

int getIndex(List* L){
    if (L->cursor) return L->index;
    else return -1;
}

void* getFront(List* L){
    return L->front->data;
}

void* getBack(List* L){
    return L->back->data;
}

void* getCursor(List* L){
    if (!L->cursor) {
        fprintf(stderr, "getCursor called when cursor is undefined\n");
        return NULL;
    }
    return L->cursor->data;
}

// Manipulation procedures ----------------------------------------------------
void moveFront(List* L){
    if (L->length > 0){
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List* L){
    if (L->length > 0){
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void moveNext(List* L){
    if (!L->cursor || L->index == L->length-1 || L->index == -1){
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->cursor = L->cursor->next;
        L->index++;
    }
}

void movePrev(List* L){
    if (!L->cursor || L->index == 0 || L->index == -1){
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->cursor = L->cursor->prev;
        L->index--;
    }
}

#endif


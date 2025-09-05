#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
        void* data;
        struct Node* prev;
        struct Node* next;
} Node;

typedef struct List {
        int length;
        int index;
        Node* front;
        Node* back;
        Node* cursor;
} List;

// Constructors / Destructors
Node* newNode(void* data);
void freeNode(Node* node);
List* newList(void);
void freeList(List* L);

// Access functions
int getLength(List* L);
int getIndex(List* L);
void* getFront(List* L);
void* getBack(List* L);
void* getCursor(List* L);

// Cursor movement
void moveFront(List* L);
void moveBack(List* L);
void moveNext(List* L);
void movePrev(List* L);

#endif


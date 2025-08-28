#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node
typedef struct NodeObj {
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

// List
typedef struct ListObj {
    Node front;
    Node back;
    int length;
    int index;
    Node cur;  // current node
} ListObj;

typedef ListObj* List;

// Constructors
List newList();
void freeList(List pL);
void clear(List pL);
// Getters
int getLength(List L);
int getIndex(List L);
int getCursor(List L);

// Setters
void set(List L, int x);

// Cursor movement
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);

// Insert
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);

// Remove
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other
void printList(FILE* out, List L);
List copyList(List L);

#endif

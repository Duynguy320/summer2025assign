#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

#ifndef LIST_C
#define LIST_C

Node *newNode(int data) {
        Node* new_node = malloc(sizeof(Node));
        if (!new_node) {
                fprintf(stderr, "malloc for node failed\n");
                exit(1);
        }
        new_node->data = data;
        new_node->prev = NULL;
        new_node->next = NULL;
        return new_node;
}

void freeNode(Node* node) {
        if (node) free(node);
}

List* newList(void) {
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

void freeList(List* L) {
        if (!L) return;

        Node* cur = L->front;
        while (cur) {
                Node* next = cur->next;
                freeNode(cur);
                cur = next;
        }
        free(L);
}

int getLength(List* L) {
        return L->length;
}

int getIndex(List* L) {
        if (L->cursor) return L->index;
        else return -1;
}

int getFront(List* L) {
        if (!L->front) {
                fprintf(stderr, "getFront called when front is undefined\n");
                return -1;
        }
        return L->front->data;
}

int getBack(List* L) {
        if (!L->back) {
                fprintf(stderr, "getBack called when back is undefined\n");
                return -1;
        }
        return L->back->data;
}

int getCursor(List* L) {
        if (!L->cursor) {
                fprintf(stderr, "getCursor called when cursor is undefined\n");
                return -1;
        }
        return L->cursor->data;
}

bool equals(List* A, List* B) {
        if (A && B) {
                bool output = getLength(A) == getLength(B);
                Node* ACur = A->front;
                Node* BCur = B->front;
                while (ACur && output) {
                        output = ACur->data == BCur->data;
                        ACur = ACur->next;
                        BCur = BCur->next;
                }
                return output;
        } else {
                fprintf(stderr, "equals called when one or both lists are NULL\n");
                return false;
        }
}

void set(List* L, int x) {
        if (L->cursor) {
                L->cursor->data = x;
        } else {
                fprintf(stderr, "cursor is null for set\n");
        }
}

void moveFront(List* L) {
        if (L->length > 0) {
                L->cursor = L->front;
                L->index = 0;
        } else {
                fprintf(stderr, "not enough length for moveFront\n");
        }
}

void moveBack(List* L) {
        if (L->length > 0) {
                L->cursor = L->back;
                L->index = L->length - 1;
        } else {
                fprintf(stderr, "not enough length for moveBack\n");
        }
}

void moveNext(List* L) {
        if (!L->cursor || L->index == L->length - 1 || L->index == -1) {
                L->cursor = NULL;
                L->index = -1;
        } else {
                L->cursor = L->cursor->next;
                L->index++;
        }
}

void movePrev(List* L) {
        if (!L->cursor || L->index == 0 || L->index == -1) {
                L->cursor = NULL;
                L->index = -1;
        } else {
                L->cursor = L->cursor->prev;
                L->index--;
        }
}

void prepend(List* L, int x) {
    if (!L) return;

    Node* new_node = newNode(x);
    new_node->next = L->front;
    new_node->prev = NULL;

    if (L->front != NULL) {
        L->front->prev = new_node;
    } else {
     
        L->back = new_node;
    }

    L->front = new_node;
    L->length++;
    if (L->index != -1) {
        L->index++;
    }
}

void append(List* L, int x) {
    if (!L) return;

    Node* new_node = newNode(x);
    new_node->prev = L->back;
    new_node->next = NULL;

    if (L->back != NULL) {
        L->back->next = new_node;
    } else {

        L->front = new_node;
    }

    L->back = new_node;
    L->length++;
}



void insertAfter(List* L, int x) {
    if (!L || !L->cursor) {
        fprintf(stderr, "insertAfter called with null list or undefined cursor\n");
        return;
    }

    Node* cur = L->cursor;
    Node* new_node = newNode(x);

    new_node->prev = cur;
    new_node->next = cur->next;

    if (cur->next != NULL) {
        cur->next->prev = new_node;
    } else {
        L->back = new_node;
    }

    cur->next = new_node;
    L->length++;
}



void insertBefore(List* L, int x) {
        if (!L || !L->cursor) {
                fprintf(stderr, "insertBefore called with null list or undefined cursor\n");
                return;
        }

        Node* cur = L->cursor;
        Node* new_node = newNode(x);

        new_node->next = cur;
        new_node->prev = cur->prev;

        if (cur->prev != NULL) {
                cur->prev->next = new_node;
        } else {
                L->front = new_node;
        }

        cur->prev = new_node;

        L->length++;
        L->index++;
}


void deleteFront(List* L);
void deleteBack(List* L);
void delete(List* L);

#endif


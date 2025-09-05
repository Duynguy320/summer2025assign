#include "List.h"

Node* newNode(void* data) {
        Node* new_node = malloc(sizeof(Node));
        if (!new_node) exit(1);
        new_node->data = data;
        new_node->prev = NULL;
        new_node->next = NULL;
        return new_node;
}

void freeNode(Node* node) {
        if (node) {
                free(node->data);
                free(node);
        }
}

List* newList(void) {
        List* L = malloc(sizeof(List));
        if (!L) exit(1);
        L->length = 0;
        L->index = -1;
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        return L;
}

void freeList(List* L) {
        if (L) {
                Node* cur = L->front;
                while (cur) {
                        Node* tmp = cur->next;
                        freeNode(cur);
                        cur = tmp;
                }
                free(L);
        }
}

int getLength(List* L) {
        return L->length;
}

int getIndex(List* L) {
        return L->index;
}

void* getFront(List* L) {
        return L->front ? L->front->data : NULL;
}

void* getBack(List* L) {
        return L->back ? L->back->data : NULL;
}

void* getCursor(List* L) {
        return L->cursor ? L->cursor->data : NULL;
}

void moveFront(List* L) {
        if (L->length > 0) {
                L->cursor = L->front;
                L->index = 0;
        }
}

void moveBack(List* L) {
        if (L->length > 0) {
                L->cursor = L->back;
                L->index = L->length - 1;
        }
}

void moveNext(List* L) {
        if (L->cursor) {
                L->cursor = L->cursor->next;
                if (L->cursor) L->index++;
                else L->index = -1;
        }
}

void movePrev(List* L) {
        if (L->cursor) {
                L->cursor = L->cursor->prev;
                if (L->cursor) L->index--;
                else L->index = -1;
        }
}


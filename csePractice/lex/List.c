#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 


//Constructors
Node newNode(int data){
	Node newN = malloc(sizeof(Node));
	newN->data = data;
	newN->prev = NULL;
	newN->next = NULL;	
	return newN;
}

List newList(){
	List L = malloc(sizeof(List));
	L->front = NULL;
	L->back = NULL;
	L->cur = NULL;
	L->index = 0;
	L->length = 0;
	return L;
	
}
//deconstructor
void freeNode(Node node) {
    if (node) {
        free(node);
    }
}
void freeList(List pL) {
	if(pL) {
		clear(pL); 
	}
	free(pL);
	pL = NULL;
}
void deepClear(List list){
	Node current = list -> back;
	while (current != NULL){
		current = current -> next;
		freeNode(current->prev);
	}
}

//getters
int getLength(List L){
	return L->length;
}
int getIndex(List L){
        return L->index;
}
int getCursor(List L){
        return L->cur->data;
}
Node getFront(List L){
	return L->front;
}
Node getBack(List L){
        return L->back;
}
bool equals(List listA, List listB){
	bool output = (listA->length == listB->length);
	if (output){
		Node nodeA = listA->back;
       		Node nodeB = listB->back;	
		while (output && nodeA && nodeB){
			output = (nodeA->data == nodeB->data);
			nodeA = nodeA->next;
			nodeB = nodeB->next;

		}
	}
	return output;
}	


//setters

void set(List L,int x){
	L->cur->data = x;
	return;
}
void clear(List pL){
	Node cur = pL->front;
	while(cur){
		cur = cur-> next;
		freeNode(cur->next);
	}
	return;
}
//manipulate cursor
void moveFront(List L){
	L->cur = L->front;
	return;
}
void moveBack(List L){
        L->cur = L->back;
        return;
}
void moveNext(List L){
        if (L && L->cur) L->cur = L->cur->next;
        return;
}
void movePrev(List L){
        if (L && L->cur) L->cur = L->cur->prev;
        return;
}
void prepend(List L, int x){
	if (L){
		Node newN = newNode(x);
		if (L->front){
			newN ->next = L->front;
			L->front = newN;
		}
                else {
                        L->back = newN;
                        L->front = newN;
                }
	}
	return;
}
void append(List L, int x){
        if (L){
		Node newN = newNode(x);
                if (L->back){
                        newN ->prev = L->back;
                        L->back = newN;
                }
		else {
			L->back = newN;
			L->front = newN;
		}
        }
        return;
}
void insertBefore(List L, int x){
	if (L && L->length && L->index >=0){
		if (L->cur == L->front) prepend(L,x);
		else{
			Node newN = newNode(x);
			newN->prev = L->cur->prev;
			newN->next = L->cur;
       			
			L->cur->prev->next = newN;
			L->cur->prev = newN;
		}
	}
	return;
}
void insertAfter(List L, int x){
        if (L && L->length && L->index >=0){
                if (L->cur == L->back) append(L,x);
                else{
                        Node newN = newNode(x);
                        newN->next = L->cur->next;
                        newN->prev = L->cur;

                        L->cur->next->prev = newN;
                        L->cur->next = newN;
                }
        }
        return;
}
void deleteFront(List L){
	if (L && L->length){
		Node oldFront = L->front;
		L->front = L->front->next;
		if (L->front){
			L->front->prev=NULL;
		}
		else{
			L->back = NULL; // if new front is null, old front was also the back
		}
		freeNode(oldFront);
		L->length --;
		L->index--;

	}
	return;
}

void deleteBack(List L){
        if (L && L->length){
                Node oldBack = L->back;
                L->back = L->back->prev;
                if (L->back){
                        L->back->next=NULL;
                }
                else{
                        L->front = NULL; // if new back is null, old back was also the front
                }
                freeNode(oldBack);
                L->length--;
        }
        return;
}
void delete(List L){
	if (L && L->cur){
		if (L->cur == L->front) deleteFront(L);
		else if (L->cur == L->back) deleteBack(L);
		else{
			L->cur->prev->next = L->cur->next;
			L->cur->next->prev = L->cur->prev;
			freeNode(L->cur);
		}
	}
	return;
}
//other
void printList(FILE *out, List L){
	if (L){
		Node cur = L->front;
		while (cur){
			fprintf(out,"%d",cur->data);
			cur = cur->next;
		}
	}
	return;
}

List copyList(List L){
	
	List output = newList();
	Node cur = L->front;
	for(int i=0; i<getLength(L); i++) {
		append(output,cur->data);
		cur=cur->next;
	}
	return output;
}

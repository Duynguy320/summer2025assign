

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
	
	int count=0;
	FILE *in, *in2, *out;
	char line[MAX_LEN];
	char* token;
	

	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	in2 = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(!in){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(!in2){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(!out){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
 
	while( fgets(line, MAX_LEN, in2) != NULL)  {
   		token = line;
   		count++;
   	}

 	char** tokenlist = calloc(count, sizeof(char*));
   	int i=0;

 
	while( fgets(line, MAX_LEN, in) != NULL)  {
		if(strcmp(line,"\n")==0) {
			token=line;
		}
		else {
			token = strtok(line, "\n");
		}
   		char* temp = calloc(count, sizeof(char*)+1);
   		strcpy(temp,token);
   		tokenlist[i] = temp;
   		i++;
   	}
   	List L = newList();
   	
   	for(int j=1; j<count; j++) {
   		char* temp = tokenlist[j];
   		int i = j-1;
   		if(getLength(L)==0) {
   			prepend(L,0);
   		}
   		if(getLength(L)>0 ) {
   			moveFront(L);
   			while( getIndex(L) != i ) {
   				moveNext(L);
   			}
   		}
   		while(i>=0 && strcmp(temp, tokenlist[getCursor(L)] ) < 0 ) {
   			movePrev(L);
   			i--;
   		}
   		if(getIndex(L) == -1 ) {
   			prepend(L,j);
   		}
   		else {
   			insertAfter(L,j);
   		}
   	}

   	moveFront(L);
   	for(int i=0; i<count; i++) {
   		fprintf(out, "%s\n", tokenlist[getCursor(L)]);
   		moveNext(L);
   	}
   	
   	
   	freeList(L);
    	for(int i=0; i<count; i++) {
    		free(tokenlist[i]);
   	}
   	free(tokenlist);
    
   	fclose(in);
   	fclose(in2);
   	fclose(out);
   
   return(0);
}






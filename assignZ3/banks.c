#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
typedef struct{
	char **array;
	int linecount;
	int linemax;
	int frontptr;
	int backptr;
	int id;
} BankLine;
BankLine banklines[3];
void resizeList(BankLine line, double factor) {
        line.linemax = line.linemax * factor;
        line.array = realloc(line.array, sizeof(char *) * line.linemax);
        if (line.array == NULL) {
                printf("Memory allocation failed!\n");
                exit(EXIT_FAILURE);
        }
}

int init(void) {
    for (int i = 0; i < (sizeof(banklines) / sizeof(banklines[0])); i++) {
        banklines[i].id = i;
        banklines[i].linecount = 0;
        banklines[i].linemax = 10;
        banklines[i].array = malloc(banklines[i].linemax * sizeof(char *));
        if (banklines[i].array == NULL) {
            printf("Memory allocation failed for line %d\n", i);
            return 1;
        }
	banklines[i].frontptr = 0;
        banklines[i].backptr = 0;
    }
    return 0;
}
int selectLine(void){
	int cur_min = INT_MAX;
	int id=0;
	for (int i = 0; i < (sizeof(banklines) / sizeof(banklines[0])); i++) {
		if (banklines[i].linecount < cur_min) {
            		cur_min = banklines[i].linecount;
        		id = i;
        	}
	}
	return id;
}
int addToQueue(char *name){
	int id = selectLine();
	banklines[id].array[banklines[id].frontptr] = name;
	banklines[id].linecount ++;
	if (banklines[id].linecount == banklines[id].linemax) resizeList (banklines[id],2);
	banklines[id].frontptr++;
	if (banklines[id].frontptr == banklines[id].linemax) banklines[id].frontptr = 0;
	printf("Added %s to Line %d\n", name,id);
	return 0;
}
char* serve(int id){
	if (banklines[id].linecount == 0){
		printf("Line %d Empty.\n",id);
		return NULL;
	}
	int temp_ptr;
	banklines[id].linecount--;
	temp_ptr = banklines[id].backptr;
	banklines[id].backptr ++;
	if (banklines[id].backptr == banklines[id].linemax) banklines[id].backptr = 0;
	return banklines[id].array[temp_ptr];

}
void status(void) {
	for (int i = 0; i < (sizeof(banklines) / sizeof(banklines[0])); i++) {
        	printf("Line %d: ", i);
        	int index = banklines[i].backptr;
        	for (int count = 0; count < banklines[i].linecount; count++) {
        		printf("\"%s\" ", banklines[i].array[index]);
        		index = (index + 1) % banklines[i].linemax;
        	}
        	printf("\n");
    	}
}
int readFile(void) {
    	FILE *file_ptr = fopen("actions.txt", "r");
    	if (file_ptr == NULL) {
        	printf("Not able to open the file.\n");
        	return 1;
    	}

    	char *line = NULL;
    	size_t len = 0;
    	ssize_t read;

    	while ((read = getline(&line, &len, file_ptr)) != -1) {
        	char *tokens[10];
        	int token_count = 0;

        	char *token = strtok(line, " \t\n");
        	while (token != NULL && token_count < 10) {
        		tokens[token_count++] = token;
        		token = strtok(NULL, " \t\n");
        	}

        	if (token_count == 0) {
        		continue;
        	}

        	if (tokens[0][0] == 'a') {
                	if (token_count < 3) {
        	        	printf("Invalid add format\n");
        	        	continue;
        		}
        		size_t name_len = strlen(tokens[1]) + strlen(tokens[2]) + 2;
        		char *name = malloc(name_len);
        		if (!name) {
				printf("Memory allocation failed for name");
                		return 1;
         		}
			strcpy(name, tokens[1]);
    			strcat(name, " ");
    			strcat(name, tokens[2]);
              		addToQueue(name);
            	
        	}else if (tokens[0][0] == 's') {
          		if (token_count < 2) {
                		printf("Invalid serve format\n");
                		continue;
            		}
            		int id = atoi(tokens[1]);
            		char* served = serve(id);
		
			if (served) printf("Served %s at line %d\n",served,id);

        	}else if (tokens[0][0] == 'c'){
		       status();
		}else {
        		printf("Unknown command: %s\n", tokens[0]);
        	}
    	}

	free(line);
	fclose(file_ptr);
	return 0;
}
int main(void){
	init();
	readFile();
	return 0;
}


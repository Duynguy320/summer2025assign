#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book{
	int id;
	char* title;
	struct Book *prev;
	struct Book *next;
} Book;


typedef struct Library{
	int bookCount;
	struct Book *head;
}Library;


Book* createBook(int id, char* title){
	Book* newBook = malloc(sizeof(Book));
	if (!newBook){
		printf("Node failed to allocate");
		exit(EXIT_FAILURE);
	}
	newBook->id = id;
	newBook->title = title;
	newBook->prev = NULL;
	newBook->next = NULL;
	return newBook;
}

void insertBook(Library *lib, Book *node, int tar_index){
	if (!lib || !node) return;
	if (node->prev != NULL || node->next != NULL || lib->head == node) {
    		printf("Warning: Attempt to insert node '%s' that might already be in the list.\n", node->title);
    		return;
	}

	node->prev = NULL;
	node->next = NULL;
	if (tar_index > lib->bookCount+1) tar_index = lib->bookCount+1;	
	if (lib->head == NULL){
		lib->head = node;
		lib->bookCount = 1;
		printf("-=-=-=-=-=-=-=-=-=-\nAdded: %s, to head\n",node->title);
		return;
	}
	if (tar_index<1){
		node->next = lib->head;
		lib->head->prev = node;
		lib->head = node;
		lib->bookCount++;
		printf("-=-=-=-=-=-=-=-=-=-\nAdded: %s, to position 1\n",node->title);
		return;
	}

	Book *current = lib->head;
	int index = 1;
	while (current->next != NULL && index < tar_index -1 ){
		current = current -> next;
		index ++;
	}

	
	if (current->next ==NULL) {
		current->next = node;
		node->prev = current;
	}
	else{
		node->next = current->next;
		node->prev = current;
		if (current->next){
			current->next->prev = node;
		}
		current->next = node;
	}
	lib->bookCount++;
	printf("-=-=-=-=-=-=-=-=-=-\nAdded: %s, to position %d\n",node->title,index+1);
}	
void delBook(Library *lib, Book *book){
	if (book == lib->head){
		lib->head = book->next;
	}
	printf("-=-=-=-=-=-=-=-=-=-\nRemoved: %s\n",book->title);
	if (book->prev) {
        	book->prev->next = book->next;
    	}
   	if (book->next) {
        	book->next->prev = book->prev;
    	}
	if (book->title) free(book->title);
	free(book);
	lib->bookCount--;
}

void removeBookByPosition(Library *lib, int position){
	if (!lib) return;
	if (position < 0 || position >= lib->bookCount) return;
	int cur_pos = 0;
	Book *cur_node = lib->head;
	
	while (cur_node!=NULL && cur_pos<position){
		cur_node = cur_node->next;
		cur_pos++;
	}
	if (cur_node!=NULL) delBook(lib, cur_node);
	return;
}
void removeBookByTitle(Library *lib, const char *title) {
    	if (!lib || !title) return;
    	Book *current = lib->head;
    	while (current) {
        	if (strcmp(current->title, title) == 0) {
            		delBook(lib, current);
            		return;
        		}
        		current = current->next;
    		}
	
}
void displayBook(Book *book){
	if (!book) return;
        printf("-=-=-=-=-=-=-=-=-=-\n");
        printf("Title: \"%s\", id: %d\n",book->title,book->id);
        printf("-=-=-=-=-=-=-=-=-=-\n");
}
void displayLibrary(Library *lib){
	Book *current = lib->head;
	
	while (current){
		displayBook(current);
		current = current->next;
	}
}


int readFile(Library *lib) {
	FILE *file_ptr = fopen("actions.txt", "r");
	if (!file_ptr) {
		printf("Not able to open the file.\n");
	return 1;
	}
    	char *line = NULL;
    	size_t len = 0;
    	ssize_t read;

    	while ((read = getline(&line, &len, file_ptr)) != -1) {
        	char *tokens[10];
        	int token_count = 0;

        	char *token = strtok(line, "-\t\n");
        	while (token != NULL && token_count < 10) {
            		tokens[token_count++] = token;
            		token = strtok(NULL, "-\t\n");
        	}

        	if (token_count == 0) continue;

        	char cmd = tokens[0][0];
	
        	if (cmd == 'P') {
      	        	int id = atoi(tokens[2]);
            		Book *book = malloc(sizeof(Book));
            		book->id = id;
            		book->title = strdup(tokens[1]);
            		book->prev = NULL;
            		book->next = NULL;
            		insertBook(lib, book,0);

        	} else if (cmd == 'A') {
            		int id = atoi(tokens[2]);
            		Book *book = malloc(sizeof(Book));
            		book->id = id;
            		book->title = strdup(tokens[1]);
            		book->prev = NULL;
            		book->next = NULL;
            		insertBook(lib, book,lib->bookCount);

        	} else if (cmd == 'I') {
            		int id = atoi(tokens[2]);
            		int pos = atoi(tokens[3]);
            		Book *book = malloc(sizeof(Book));
            		book->id = id;
            		book->title = strdup(tokens[1]);
            		book->prev = NULL;
            		book->next = NULL;
            		insertBook(lib, book, pos);

        	} else if (cmd == 'R') {
            		int pos = atoi(tokens[1]);
            		removeBookByPosition(lib, pos);

        	} else if (cmd == 'T') {
            		removeBookByTitle(lib, tokens[1]);

        	} else if (cmd == 'D') {
            		displayLibrary(lib);

	} else {
        	printf("Unknown command: %s\n", tokens[0]);
        }
    }

    free(line);
    fclose(file_ptr);
    return 0;
}


int main(void){
	Library *lib = malloc(sizeof(Library));
	lib->head = NULL;
	lib->bookCount = 0;
	readFile(lib);
	return 0;
}

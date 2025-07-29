#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;
	int id;
	int *classes;
	int num_classes;
} Student;

Student *STUDENTS = NULL;
int STUDENT_COUNT = 0;
int MAX_STUDENTS;

void resizeList(void) {
	MAX_STUDENTS = MAX_STUDENTS * 2;
	STUDENTS = realloc(STUDENTS, sizeof(Student) * MAX_STUDENTS);
	if (STUDENTS == NULL) {
        	fprintf(stderr, "Memory allocation failed!\n");
        	exit(EXIT_FAILURE);
        }
}
void initStudentList(void) {
    MAX_STUDENTS = 4;
    STUDENTS = malloc(sizeof(Student) * MAX_STUDENTS);
    if (STUDENTS == NULL) {
        fprintf(stderr, "Initial allocation failed!\n");
        exit(EXIT_FAILURE);
    }
}

void freeStudentList() {
    for (int i = 0; i < STUDENT_COUNT; i++) {
        free(STUDENTS[i].name);
        free(STUDENTS[i].classes);
    }
    free(STUDENTS);
    STUDENTS = NULL;
    STUDENT_COUNT = 0;
    MAX_STUDENTS = 0;
}
int readFile(void){
	FILE *file_ptr;
	file_ptr = fopen("studentList.txt", "r");
	if(file_ptr == NULL) {
		printf("Not able to open the file.");
		fclose(file_ptr);
		return 1;
	}
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line, &len, file_ptr)) != -1) {
        
	
        	char *tokens[100];
        	int token_count = 0;

        	char *token = strtok(line," \n");
        	while (token != NULL && token_count < 100) {
        		tokens[token_count++] = token;
        		token = strtok(NULL, " \t\n");
        	}
	
        	if (token_count < 3) {
        		continue; 
        	}

        
        	Student s;
		s.num_classes = token_count - 3;
        
        	size_t name_len = strlen(tokens[0]) + strlen(tokens[1]) + 2;
        	s.name = malloc(name_len);
        	snprintf(s.name, name_len, "%s %s", tokens[0], tokens[1]);

        
        	s.id = atoi(tokens[2]);

        	s.num_classes = token_count - 3;
        	s.classes = malloc(sizeof(int) * s.num_classes);
        	for (int i = 0; i < s.num_classes; i++) {
        		s.classes[i] = atoi(tokens[i + 3]);
        	}
        	if (STUDENT_COUNT >= MAX_STUDENTS) {
    			resizeList();
		}
        	STUDENTS[STUDENT_COUNT] = s;
		STUDENT_COUNT++;
	}
	return 0;
}

Student* getStudent(int index) {
	if (index < 0 || index >= STUDENT_COUNT) return NULL;
	return &STUDENTS[index];
}
void setStudent(int index, Student newStudent) {
    	if (index < 0 || index >= STUDENT_COUNT) return;
    	free(STUDENTS[index].name);
    	free(STUDENTS[index].classes);
	STUDENTS[index] = newStudent;
}


void printStudent(int index) {
    	Student* s = getStudent(index);
    	if (!s) {
        	printf("Student index %d out of range.\n", index);
        	return;
    	}
	printf("================\n");
	printf("%s\n", s->name);
	printf("%d\n", s->id);
	printf("List of classes:\n");
	for (int i = 0; i < s->num_classes; i++) {
		printf("%d\n", s->classes[i]);
	}
	printf("================\n");
}
void searchStudent(const char *attribute, const char *value) {
    	int found = 0;

    	for (int i = 0; i < STUDENT_COUNT; i++) {
        	Student *s = &STUDENTS[i];

        	if (strcmp(attribute, "name") == 0) {
            		if (strcmp(s->name, value) == 0) {
                		printStudent(i);
                		found = 1;
            		}

        	} else if (strcmp(attribute, "id") == 0) {
            		int id_to_find = atoi(value);
            		if (s->id == id_to_find) {
                		printStudent(i);
                		found = 1;
            		}

        	} else if (strcmp(attribute, "classes") == 0) {
            		int class_id = atoi(value);
            		for (int j = 0; j < s->num_classes; j++) {
                		if (s->classes[j] == class_id) {
                    			printStudent(i);
                    			found = 1;
                    			break;
                		}
            		}
        	} else {
            		printf("Unknown attribute: %s\n", attribute);
        	    return;
        	}
    	}
    	if (!found) {
		printf("No matching student found for %s = %s\n", attribute, value);
	}
}
int main(void){
	initStudentList();
	readFile();
	printStudent(0);
	printStudent(1);
	printStudent(2);
	searchStudent("name", "John Doe");
	searchStudent("name", "Sarah Wilson");
	searchStudent("name", "Not Real"); 
	searchStudent("id", "000003");
	searchStudent("id", "000010");
	searchStudent("id", "999999");  
	searchStudent("classes", "12345");
	searchStudent("classes", "55555");
	searchStudent("classes", "33333");
	searchStudent("classes", "00000"); 
	return 0;
}

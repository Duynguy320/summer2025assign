Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c
ListTest: ListTest.o List.o
	gcc -o ListTest ListTest.o List.o



clean :
	rm -f Lex Lex.o List.o

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8

int solutionCount = 0;
char board[N][N];


void printSolution(void) {
	solutionCount++;
	printf("Solution %d:\n", solutionCount);
    	for (int i = 0; i < N; i++) {
        	for (int j = 0; j < N; j++) {
            		printf("%c", board[i][j]);
        	}
        	printf("\n");
    	}
    	printf("\n");
}

bool isValid(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i][col] == 'Q')
            return false;
    for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q')
            return false;
    for (int i = row-1, j = col+1; i >= 0 && j < N; i--, j++)
        if (board[i][j] == 'Q')
            return false;
    return true;
}

void solve(int row) {
    if (row == N) {
        printSolution();
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isValid(row, col)) {
            board[row][col] = 'Q';
            solve(row + 1);
            board[row][col] = '.';
        }
    }
}

int main() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = '.';
    solve(0);
    printf("Total solutions: %d\n", solutionCount);
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "philos.h"


int MAX_ROLLS = 3;
int STARTING_MONEY = 3;
int MAX_PLAYERS = 14;
/*
 * getUserInputs
 * Gets Seed and Number of Players from the user
 * inputs: 
 * 	- seed
 * 	- number if players
 * outputs:
 * 	- false if no errors
 * 	- changes the pointers
*/

int getUserInputs(int *seed, int *num_players){
	printf("Enter the Seed: \n");
	scanf("%d",seed);
	srand(*seed);
	while (getchar() != '\n'){
		//flush characters
	}
        printf("Enter the number of players: \n");
        scanf("%d",num_players);
	if (*num_players > MAX_PLAYERS) *num_players = 14;
	return 0;
}
/*
 *process roll
 * takes roll and decies what to do with it
 * pass, right, left, center, etc
 * prinmts what roll so i know whats appening
 * inputs:
 *      - roll
 * outputs:
 *      - N/A
*/
void processRoll(int player, int roll, int starting_players, int *scoreStorage, int *cur_p, int *rolls) {
	int target = player;
	switch (roll) {
	case 0: // Right
		printf("Player %d rolled R\n", player);
		scoreStorage[player]--;
		if (scoreStorage[player] == 0) (*cur_p)--;
		if (player == starting_players - 1) target = 0;
		else target ++;
		scoreStorage[target]++;
		if (scoreStorage[target] == 1) (*cur_p)++;
		break;

        case 1: // Left
		printf("Player %d rolled L\n", player);
		scoreStorage[player]--;
		if (scoreStorage[player] == 0) (*cur_p)--;
                if (player == 0) target = starting_players - 1;
		else target --;
		scoreStorage[target]++;
		if (scoreStorage[target] == 1) (*cur_p)++;
		break;
        case 2: // Center
		printf("Player %d rolled C\n", player);
		scoreStorage[player]--;
		if (scoreStorage[player] == 0) (*cur_p)--;
        	break;
        default: // Pass
        	printf("Player %d rolled P\n", player);
		*rolls = -1;
		break;
    }
}
/* 
 * gameLoop:
 * dictates how the game is run
 * Loops through each player and applies the rules and rolls the dice
 * inputs: starting players
 * outputs: game logs to consule
*/
int gameLoop(const int starting_players){
	int scoreStorage[starting_players];
	for (int i = 0; i < starting_players; i++) {
    		scoreStorage[i] = STARTING_MONEY;
	}
	int cur_p = starting_players;
	//while at least 2 active players, run game
	while (cur_p > 1){
		//main loop
		for (int player = 0;player < starting_players;player++){
			//check if 1 player left in after resolving a players turn
			if (cur_p == 1) break;
			if (scoreStorage[player] > 0) {
			
				for (int rolls = scoreStorage[player];rolls > 0; rolls--){
				int getUserInputs(int *seed, int *num_players);
				if (rolls > MAX_ROLLS) rolls = MAX_ROLLS;
				int dice = rand() % (6);
		
				processRoll(player, dice, starting_players, scoreStorage, &cur_p, &rolls);
				printf("current standings: [");
				for (int k = 0; k < starting_players; k++) {
					printf("%d", scoreStorage[k]);
					if (k != starting_players - 1) printf(", ");
				}
				printf("]\n");
								
				}
			}
		}
	}
	for (int i = 0; i < starting_players;i++){
		if (scoreStorage[i]){
			printf("The Winner is: %s\n", philosophers[i]);
			printf(", who won: %d\n", starting_players*STARTING_MONEY);
			return 0;	
		}
	}
	//returns true if no winners are found
	return 1;
}

int main(void){
	int seed;
	int num_players;
	getUserInputs(&seed,&num_players);
	gameLoop(num_players);
	return 0;
}

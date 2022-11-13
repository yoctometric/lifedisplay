#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "conway.h"

// init board to random state
void random_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	//init seed
	srand(time(NULL));

	//. populate board with 1 or zero
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = rand() % 2;
		}
	}
}


// prints the board state to the terminal
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	printf("Board state:\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
}

// step the board forward one time step
void step_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	char newb[BOARD_SIZE][BOARD_SIZE];
	char neigh;

	// apply the conways rules by iterating through old array and applying to new array
	for (int x=0; x < BOARD_SIZE; x++) {
		for (int y=0; y < BOARD_SIZE; y++) {
			// get num neighbors
			neigh = 0;
			neigh += get_state(board, x-1, y-1);
			neigh += get_state(board, x-1, y);
			neigh += get_state(board, x-1, y+1);
			neigh += get_state(board, x, y-1);
			neigh += get_state(board, x, y+1);
			neigh += get_state(board, x+1, y-1);
			neigh += get_state(board, x+1, y);
			neigh += get_state(board, x+1, y+1);

			// now act based on how many neighbors the cell has (if alive):
			if (board[x][y] == 1) {
				// 1: <2 neigh, die of lonliness
				if (neigh < 2) newb[x][y] = 0;
				// 2. >3 neigh, die of overcrowding
				else if (neigh > 3) newb[x][y] = 0;
				// 3. 2 or 3 neigh, continue living
				else newb[x][y] = 1;
			}
			// and for dead cells:
			else {
				// if exactly 3 neighbors, come to life
				if (neigh == 3) newb[x][y] = 1;
				else newb[x][y] = 0;
			}
		}
	}

	// finally, overwrite the old board.
	memcpy(board, newb, BOARD_SIZE*BOARD_SIZE);
}

// indexes the board and returns the value at that index
char get_state(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
	// clamp indices
	if (x < 0) x += BOARD_SIZE;
	else x = x % BOARD_SIZE;

	if (y < 0) y += BOARD_SIZE;
	else y = y % BOARD_SIZE;

	return board[x][y];
}

// set the board value at indicex (x,y). returns the old state
char set_state(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, char val) {
        // clamp indices
        if (x < 0) x += BOARD_SIZE;
        else x = x % BOARD_SIZE;

        if (y < 0) y += BOARD_SIZE;
        else y = y % BOARD_SIZE;

	char old = board[x][y];
	board[x][y] = val;

	return old;
}


// simple visual testing to make sure everything works properly
int main() {
	char board[BOARD_SIZE][BOARD_SIZE];
	random_board(board);
	print_board(board);
	step_board(board);
	print_board(board);
	step_board(board);
	print_board(board);
}


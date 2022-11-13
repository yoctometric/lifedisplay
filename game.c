// the main game file

#include <unistd.h>
#include <stdio.h>

#include "conway.h"
#include "ht16K33.h"
#include "game.h"

// write the board state to the screen
int write_board(int fd, char board[BOARD_SIZE][BOARD_SIZE]) {
	// copy board into buffer
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			// for draw_pixel(x,y) the x is actually y and the y is actually x. x += 8 makes it red.
			if (board[x][y]) {
				draw_pixel(x, BOARD_SIZE-1-y);
			}
		}
	}


	write_display(fd);
	return 0;
}


int main() {
	int fd;

	// set up the display
	fd = setup_ht16K33();
	char c; // tempvar
	char board[BOARD_SIZE][BOARD_SIZE];
//	random_board(board);
	glider_board(board);


	clear_screen(fd);
	usleep(1000000);

	// main loop
	while (1) {
		clear_screen(fd);
		write_board(fd, board);
		print_board(board);
		step_board(board);
		scanf("%c", &c);
	}

	clear_screen(fd);
	usleep(1000000);
	disable_ht16K33(fd);

	return 0;
}

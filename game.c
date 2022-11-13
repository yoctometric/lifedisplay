// the main game file

#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/gpio.h>

#include "conway.h"
#include "ht16K33.h"
#include "buttons.h"
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

// enter edit mode
void enter_edit(int * mode, int * cursor_x, int * cursor_y) {
	*mode = MODE_EDIT;
	*cursor_x = 0;
	*cursor_y = 0;

	printf("Entered edit mode\n");
}

//enter play mode
void enter_play(int * mode) {
	*mode = MODE_PLAY;

	printf("Entered play mode\n");

}

// increments the cursor position
void inc_cursor(int * cursor_x, int * cursor_y) {
	*cursor_x = *cursor_x + 1;
	if (*cursor_x >= BOARD_SIZE) {
		*cursor_x = *cursor_x % BOARD_SIZE;
		*cursor_y = *cursor_y + 1;
		if (*cursor_y >= BOARD_SIZE) {
			*cursor_y = *cursor_y % BOARD_SIZE;
		}
	}

	printf("Cursor is at (%d, %d)\n", *cursor_x, *cursor_y);
}



int main() {
	int ht_fd, b_fd;
	int cursor_x, cursor_y;
	int mode;
	int frame_counter = 0;


	// set up the buttons
        b_fd = open_gpio();

        int button_frames[NUM_BUTTONS] = {0, 0, 0};
        struct gpiohandle_request buttons[NUM_BUTTONS];

        init_button(BUTTON_1, b_fd, &buttons[0]);
        init_button(BUTTON_2, b_fd, &buttons[1]);
        init_button(BUTTON_3, b_fd, &buttons[2]);


	// set up the conway board
	char board[BOARD_SIZE][BOARD_SIZE];
	empty_board(board);

	// set up the display
	ht_fd = setup_ht16K33();
	clear_screen(ht_fd);
	usleep(FRAME);

	// set the game mode to EDIT
	enter_edit(&mode, &cursor_x, &cursor_y);

	// main loop
	while (1) {
		update_buttons(buttons, button_frames);

		// handle play mode
		if (mode == MODE_PLAY) {
			//only step through the game if enough 'frames' have passed
			if (frame_counter % FRAMES_PER_GAMESTEP == 0) {
				clear_screen(ht_fd);
				write_board(ht_fd, board);
				step_board(board);
			}

			// read to check for a mode change
			if (button_frames[0] > FRAMES_BUTTON_ACTIVATION) {
				button_frames[0] = 0;
                                enter_edit(&mode, &cursor_x, &cursor_y);
			}

		}
		// handle edit mode
		else if (mode == MODE_EDIT) {
			// move the cursor if the move button is pressed
			if (button_frames[2] > FRAMES_BUTTON_ACTIVATION) {
				button_frames[2] = 0;

				inc_cursor(&cursor_x, &cursor_y);
			}

			// toggle the curent cell and render
			if (button_frames[1] > FRAMES_BUTTON_ACTIVATION) {
				button_frames[1] = 0;

				toggle_state(board, cursor_x, cursor_y);
			}

                        // read to check for a mode change
                        if (button_frames[0] > FRAMES_BUTTON_ACTIVATION) {
				button_frames[0] = 0;
				enter_play(&mode);
                        }

			clear_screen(ht_fd);
			write_board(ht_fd, board);
			draw_cursor(cursor_x, cursor_y);
			write_display(ht_fd);
		}

		// handle frames
		usleep(FRAME);
		frame_counter++;
		if (frame_counter > 9999) frame_counter -= 9999;
	}

	clear_screen(ht_fd);
	usleep(1000000);
	disable_ht16K33(ht_fd);

	return 0;
}

// h file for the main conways functions

#define BOARD_SIZE 8

// init board randomly
void random_board(char board[BOARD_SIZE][BOARD_SIZE]);

// init board with a glider
void glider_board(char board[BOARD_SIZE][BOARD_SIZE]);

// prints the board state to the terminal
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);

// step the board forward one time step
void step_board(char board[BOARD_SIZE][BOARD_SIZE]);

// grabs state of cell
char get_state(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);

// sets the state of a cell
char set_state(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, char val);

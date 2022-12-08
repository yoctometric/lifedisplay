
// the lenght of time a frame lasts
#define FRAME 20000
#define FRAMES_PER_GAMESTEP 25
#define FRAMES_BUTTON_ACTIVATION 5

#define MODE_EDIT 1
#define MODE_PLAY 0

// writes the game state to the screen
int write_board(int fd, char board[8][8]);
void enter_edit(int * mode, int * cursor_x, int * cursor_y);
void enter_play(int * mode);
void inc_cursor(int * cursor_x, int * cursor_y);

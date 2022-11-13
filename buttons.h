// buttons h file
#define BUTTON_1 23
#define BUTTON_2 24
#define BUTTON_3 25


struct gpiohandle_request;
struct gpiohandle_data;

int init_buttons();
void terminate_buttons();
int read_pin(int pin);
int await_input();

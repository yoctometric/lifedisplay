// buttons h file
#define BUTTON_1 23
#define BUTTON_2 24
#define BUTTON_3 25



int open_gpio();
void init_button(int pin, int fd, struct gpiohandle_request* req);
int read_pin(struct gpiohandle_request* req);

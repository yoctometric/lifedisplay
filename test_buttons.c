// tests for the gpio buttons

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include "buttons.h"

int main() {
	int fd;

	fd = open_gpio();

	int button_frames[NUM_BUTTONS] = {0, 0, 0};
	struct gpiohandle_request buttons[NUM_BUTTONS];

	init_button(BUTTON_1, fd, &buttons[0]);
	init_button(BUTTON_2, fd, &buttons[1]);
	init_button(BUTTON_3, fd, &buttons[2]);


	while(1) {
		usleep(10000);

		update_buttons(buttons, button_frames);
		printf("B1: %d B2: %d B3: %d\n", button_frames[0], button_frames[1], button_frames[2]);

	}

	close(fd);

	return 0;
}

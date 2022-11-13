// tests for the gpio buttons

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include "buttons.h"

int main() {
	int read, fd;

	fd = open_gpio();

	struct gpiohandle_request req1;
	struct gpiohandle_request req2;
	struct gpiohandle_request req3;

	init_button(BUTTON_1, fd, &req1);
	init_button(BUTTON_2, fd, &req2);
	init_button(BUTTON_3, fd, &req3);


	while(1) {
		usleep(10000);

		read = read_pin(&req1);
		printf("Read %d\n", read);

	}

	close(fd);

	return 0;
}

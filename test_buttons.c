// tests for the gpio buttons

#include <stdio.h>


#include "buttons.h"

int main() {
	int read, gpio_fd;
	init_buttons();

	while (1) {
		read = read_pin(BUTTON_1);
		printf("Read %d\n", read);
	}


	terminate_buttons();
	return 0;
}

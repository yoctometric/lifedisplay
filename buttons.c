// GPIO button input handling

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <linux/gpio.h>

#include <pigpio.h>

#include "buttons.h"

// sets up the buttons for use
int init_buttons() {
	int res = gpioInitialise();
	if (res < 0) {
		printf("Error initialising GPIO\n");
		exit(1);
	}

	gpioSetMode(BUTTON_1, PI_INPUT);
	gpioSetMode(BUTTON_2, PI_INPUT);
	gpioSetMode(BUTTON_3, PI_INPUT);

	return res;
}

// cleans up the gpio environment
void terminate_buttons() {
	gpioTerminate();
}


// simple function to read pin
int read_pin(int pin) {
	int res;
	res = gpioRead(pin);
	return res;
}



// halts program until a gpio button press is detected and returns that button
int await_input() {

	return 0;
}

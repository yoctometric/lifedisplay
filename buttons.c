// GPIO button input handling

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <linux/gpio.h>

#include "buttons.h"


// returns the file descriptor of the gpio device
int open_gpio() {
	int fd;

        fd = open("/dev/gpiochip0", O_RDWR);

	if (fd < 0) {
		printf("Failed to open the gpio device\n");
		exit(1);
	}

	return fd;
}

// sets up the button for use
void init_button(int pin, int fd, struct gpiohandle_request* req) {
	int rv;

        // setup request struct
        memset(req, 0, sizeof(struct gpiohandle_request)); // zero contents
        req->flags = GPIOHANDLE_REQUEST_INPUT; // requesting input this time
        req->lines = 1;
        req->lineoffsets[0] = pin;
        // get a handle for the config
        rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, req);
        if (rv < 0) {
                printf("Error getting config handle %s", strerror(errno));
                exit(1);
        }


}


// simple function to read pin
int read_pin(struct gpiohandle_request* req) {
        int rv;
	struct gpiohandle_data data;
        memset(&data, 0, sizeof(data)); // wipe data
        rv = ioctl(req->fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
        if (rv < 0) {
                printf("Error reading pin %s\n", strerror(errno));
        }
        return data.values[0];


}

// updates the amount of frames each button has been held down
void update_buttons(struct gpiohandle_request reqs[NUM_BUTTONS], int button_frames[NUM_BUTTONS]) {
	int res;
	for (int i = 0; i < NUM_BUTTONS; i++) {
		res = read_pin(&reqs[i]);
		if (res == 0) {
			button_frames[i] = 0;
		}
		button_frames[i] += res;
	}
}



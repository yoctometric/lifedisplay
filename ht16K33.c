// Code for communicating with the ht16K33 LED matrix backpack via i2c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "ht16K33.h"

int display_buffer[16]; // actually define the displaybuffer here

// sets up the display. Returns the file descriptor, or returns -1 if an error occured.
int setup_ht16K33 () {
	int fd;
	int res;
	char buffer;

	// open the i2c device
	fd = open("/dev/i2c-1", O_RDWR);
	if (fd < 0) return -1;

	// set the device address
	res = ioctl(fd, I2C_SLAVE, DEVICE_ADDRESS);
	if (res < 0) return -1;

	// turn on the oscillator
	buffer = SYS_SET | 1;
	res = write(fd, &buffer, 1);
	if (res < 0) return -1;

	// clear the screen
	clear_screen(fd);

	// set brightness to (mostly) full
	buffer = (0xE << 4) | (0x8);
	res = write(fd, &buffer, 1);

	// turn on the display
	buffer = DISP_SET | 1;
	res = write(fd, &buffer, 1);
	if (res < 0) return -1;

	return fd;
}


// turns off the display and puts it into standby mode. Also closes the file descriptor.
int disable_ht16K33 (int fd) {
	int res;
	int buffer;

	buffer = SYS_SET | 0;
	res = write(fd, &buffer, 1);
	if (res < 0) return -1;

	close(fd);

	return 0;
}


// draws a pixel to thge display buffer. Only actually displayed on screen after write_display() is called
int draw_pixel(unsigned char x, unsigned char y) {
	if ((y < 0) || (y > 8)) return -1;
	if ((x < 0) || (x > 16)) return -1;

	display_buffer[y] |= 1 << x;

	return 0;
}

// draws the cursor (in red) to the display buffer
int draw_cursor(unsigned char x, unsigned char y) {
        if ((y < 0) || (y > 8)) return -1;
        if ((x < 0) || (x > 16)) return -1;

        display_buffer[7 - y] |= 1 << (x + 8);

        return 0;

}

// write the buffer to the display (source: adafruit)
int write_display(int fd) {
	uint8_t buffer[17];

	buffer[0] = 0x00;

	for (uint8_t i = 0; i < 8; i++) {
		buffer[1 + 2 * i] = display_buffer[i] & 0xff;
		buffer[2 + 2 * i] = display_buffer[i] >> 8;
	}

	int res = write(fd, buffer, 17);
	return res;
}


// completely clears the screen
int clear_screen(int fd) {
	for (int i = 0; i < 8; i++) {
		display_buffer[i] = 0;
	}

	write_display(fd);
	return 0;
}




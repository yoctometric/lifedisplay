// Code for communicating with the ht16K33 LED matrix backpack via i2c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "ht16K33.h"


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


// writes a column <col> (0 - 255) to row <row> (0 - 7), with alt_color either 0 or 1
int write_col(int fd, int col, unsigned char row, int alt_color) {
	unsigned char buffer[2];

	buffer[0] = (row * 2) + alt_color;
	buffer[1] = col;
	write_buf(fd, buffer);
}




// writes the buffer to the display
int write_buf(int fd, char * buffer) {
	int res;
	int len = sizeof(buffer) / sizeof(buffer[0]);

	// finn the write buffer with <buffer> and pad the rest with zeroes
	unsigned char b[17];
	for (int i = 0; i < len; i++) b[i] = buffer[i];
	for (int i = len; i < 17; i++) b[i] = 0;

	// write it
	res = write(fd, b, len);
	if (res < 0) return -1;

	return 0;
}


// completely clears the screen
int clear_screen(int fd) {
	unsigned char buffer[17];
	for(int i = 0; i < 17; i++) {
		buffer[i] = 0;
	}

	// clear each address
	for(int a = 0; a < 16; a++) {
		buffer[0] = a;
		write(fd, buffer, 17);
	}
}




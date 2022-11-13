// Tests the display
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "ht16K33.h"


int main () {
	int fd;
	unsigned char buffer[17];

	// zero the buffer


	fd = setup_ht16K33();
	if (fd < 0) printf("Error setting up the display\n");

	clear_screen(fd);

	buffer[0] = 0;
	for (int i = 1; i < 17; i++) {
		for (int b = 1; b < 17; b++) buffer[b] = 0;
		buffer[i] = 0xf;
		write_buf(fd, buffer);
		usleep(500000);
	}



	usleep(2000000);


	write_col(fd, 1, 0, 0);

	for (int i = 0; i < 7; i++) {
//		clear_screen(fd); // if the screen is not cleared each time a col is written, it fails. Find solution
		write_col(fd, 3, i, 0);
		usleep(100000);
	}


	usleep(2000000);


	disable_ht16K33(fd);

	printf("Completed test_display\n");
	return 0;
}

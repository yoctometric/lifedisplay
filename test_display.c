// Tests the display
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "ht16K33.h"


int main () {
	int fd;
	unsigned char buffer[17];

	fd = setup_ht16K33();
	usleep(100000);


	draw_pixel(3+8, 3);
	draw_pixel(1, 3);
	draw_pixel(2, 3);
	draw_pixel(4, 3);
	write_display(fd);

	usleep(2000000);

}

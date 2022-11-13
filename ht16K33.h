#ifndef HT16K33_H_
#define HT16K33_H_

// An interface for communicating with the ht16K33 LED matrix backpack
#define DEVICE_ADDRESS 0x70 // The default address of the display

// commands
#define SYS_SET		(0x2 << 4)
#define ROW_SET		(0xA << 4) | 0
#define INT_SET		(0xA << 4) | 1
#define DISP_SET	(0x8 << 4)

extern int display_buffer[16]; // declare it

int setup_ht16K33(void);
int disable_ht16K33(int fd);
int clear_screen(int fd);
int write_display(int fd);
int draw_pixel(unsigned char x, unsigned char y);

#endif // HT16K33_H_

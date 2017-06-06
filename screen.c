#include "screen.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <stdio.h>

#include "keyboard.h"

struct buffer_t buffer;

void reset_cursor() {
	buffer_append(&buffer, "\x1b[H", 3);
}

void hide_cursor() {
	buffer_append(&buffer, "\x1b[?25l", 6);
}

void show_cursor() {
	buffer_append(&buffer, "\x1b[?25h", 6);
}

void clear_screen() {
	buffer_append(&buffer, "\x1b[2J", 4);
}

void draw_rows() {
	for(int y = 0; y < config.num_rows; y++) {
		buffer_append(&buffer, "~", 1);
		buffer_append(&buffer, "\x1b[K", 3);
		if(y < config.num_rows - 1) {
			buffer_append(&buffer, "\r\n", 2);
		}
	}
}

void draw_screen() {
	buffer.d = NULL;
	buffer.len = 0;

	hide_cursor();
	reset_cursor();
	draw_rows();
	reset_cursor();
	show_cursor();

	write(STDOUT_FILENO, buffer.d, buffer.len);
	//buffer_free(&buffer);
}

bool get_cursor_position(int* rows, int* cols) {
	if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) {
		return false;
	}
	char seq[32];
	unsigned int i = 0;

	while(i < sizeof(seq) - 1) {
		if(read(STDIN_FILENO, &seq[i], 1) != 1) {
			break;
		}
		if(seq[i] == 'R') {
			break;
		}
		i++;
	}
	seq[i] = '\0';

	if(seq[0] != '\x1b' || seq[1] != '[') {
		return false;
	}
	if(sscanf(&seq[2], "%d;%d", rows, cols) != 2) {
		return false;
	}

	return true;
}

bool obtain_window_size(int* rows, int* cols) {
	struct winsize size;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1 || size.ws_col == 0) {
		if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) {
			return false;
		}
		return get_cursor_position(rows, cols);
	}

	*rows = size.ws_row;
	*cols = size.ws_col;

	return true;
}


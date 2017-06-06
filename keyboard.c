#include "keyboard.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "process.h"
#include "screen.h"
#include "terminal.h"

extern struct config_t config;

char read_key() {
	int bytes_read;
	char c;
	while((bytes_read = read(STDIN_FILENO, &c, 1)) == -1) {
		if(bytes_read == -1 && errno != EAGAIN) {
			exit_error("read");
		}
	}
	return c;
}

void update_cursor(char key) {
	switch(key) {
		case 'a':
			config.cursor_x--;
			break;
		case 'd':
			config.cursor_x++;
			break;
		case 'w':
			config.cursor_y--;
			break;
		case 's':
			config.cursor_y++;
			break;
	}
}

void process_keypress() {
	char c = read_key();

	switch(c) {
		case CTRL_KEY('q'):
			clear_screen();
			exit(EXIT_SUCCESS);
			break;

		case 'w':
		case 's':
		case 'a':
		case 'd':
			update_cursor(c);
			break;
	}
}


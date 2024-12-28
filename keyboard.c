#include "keyboard.h"

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "process.h"
#include "screen.h"
#include "terminal.h"

enum editor_key {
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,

	DELETE_KEY,

	HOME_KEY,
	END_KEY,

	PAGE_UP,
	PAGE_DOWN
};

int read_key() {
	ssize_t bytes_read;
	char c;
	while((bytes_read = read(STDIN_FILENO, &c, 1)) == -1) {
		if(bytes_read == -1 && errno != EAGAIN) {
			exit_error("read");
		}
	}

	if(c == '\x1b') {
		char seq[3];

		if(read(STDIN_FILENO, &seq[0], 1) != 1) {
			return c;
		}
		if(read(STDIN_FILENO, &seq[1], 1) != 1) {
			return c;
		}

		if(seq[0] == '[') {
			if(seq[1] >= '0' && seq[1] <= '9') {
				if(read(STDIN_FILENO, &seq[2], 1) != 1) {
					return c;
				}
				if(seq[2] == '~') {
					switch(seq[1]) {
						case '3':
							return DELETE_KEY;
						case '1':
						case '7':
							return HOME_KEY;
						case '4':
						case '8':
							return END_KEY;
						case '5': return PAGE_UP;
						case '6': return PAGE_DOWN;
					}
				}
			} else {
				switch(seq[1]) {
					case 'A': return ARROW_UP;
					case 'B': return ARROW_DOWN;
					case 'C': return ARROW_RIGHT;
					case 'D': return ARROW_LEFT;
					case 'H': return HOME_KEY;
					case 'F': return END_KEY;
				}
			}
		} else if(seq[0] =='O') {
			switch(seq[1]) {
				case 'H': return HOME_KEY;
				case 'F': return END_KEY;
			}
		}
	}

	return c;
}

void update_cursor(int key) {
	switch(key) {
		case ARROW_LEFT:
			if(config.cursor_x > 0) {
				config.cursor_x--;
			}
			break;
		case ARROW_RIGHT:
			if(config.cursor_x != config.num_cols - 1) {
				config.cursor_x++;
			}
			break;
		case ARROW_UP:
			if(config.cursor_y > 0) {
				config.cursor_y--;
			}
			break;
		case ARROW_DOWN:
			if(config.cursor_y != config.num_rows - 1) {
				config.cursor_y++;
			}
			break;
	}
}

void process_keypress() {
	const int c = read_key();

	switch(c) {
		case CTRL_KEY('q'):
			clear_screen();
			exit(EXIT_SUCCESS);

		case HOME_KEY:
			config.cursor_x = 0;
			break;
		case END_KEY:
			config.cursor_x = config.num_cols - 1;
			break;

		case PAGE_UP:
		case PAGE_DOWN:
			{
				int times = config.num_rows;
				while(times--) {
					update_cursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
				}
			}
			break;

		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			update_cursor(c);
			break;
	}
}


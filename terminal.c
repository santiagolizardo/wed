#include "terminal.h"

#include <unistd.h>

#include "process.h"
#include "screen.h"

void init_config() {
	config.cursor_x = config.cursor_y = 0;

	if(obtain_window_size(&config.num_rows, &config.num_cols) == false) {
		exit_error("obtain_window_size");
	}
}

void enable_raw_mode() {
	if(tcgetattr(STDIN_FILENO, &config.orig_termios) == -1) {
		exit_error("tcgetattr");
	}
	
	struct termios raw_termios = config.orig_termios;
	raw_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw_termios.c_oflag &= ~(OPOST);
	raw_termios.c_cflag &= ~(CS8);
	raw_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw_termios.c_cc[VMIN] = 0;
	raw_termios.c_cc[VTIME] = 1;
	
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios) == -1) {
		exit_error("tcsetattr");
	}
}

void disable_raw_mode() {
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &config.orig_termios) == -1) {
		exit_error("tcsetattr");
	}
}


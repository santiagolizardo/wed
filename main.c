#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

struct termios orig_termios;

void exit_error(const char *s) {
	perror(s);
	exit(EXIT_FAILURE);
}

void enable_raw_mode() {
	if(tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
		exit_error("tcgetattr");
	}
	
	struct termios raw_termios = orig_termios;
	raw_termios.c_iflag &= ~(IXON | ICRNL);
	raw_termios.c_oflag &= ~(OPOST);
	raw_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw_termios.c_cc[VMIN] = 0;
	raw_termios.c_cc[VTIME] = 1;
	
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios) == -1) {
		exit_error("tcsetattr");
	}
}

void disable_raw_mode() {
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
		exit_error("tcsetattr");
	}
}

int main() {
	enable_raw_mode();
	atexit(disable_raw_mode);

	char c;
	while(true) {
		c = '\0';
		if(read(STDIN_FILENO, &c, 1) == -1 || errno == EAGAIN) {
			exit_error("read");
		}
		if(iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
		if(c == 'q') break;
	}
	return EXIT_SUCCESS;
}


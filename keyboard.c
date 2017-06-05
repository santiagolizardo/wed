#include "keyboard.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "process.h"
#include "screen.h"

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

void process_keypress() {
	char c = read_key();

	switch(c) {
		case CTRL_KEY('q'):
			clear_screen();
			exit(EXIT_SUCCESS);
			break;
	}
}


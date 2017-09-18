#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "keyboard.h"
#include "process.h"
#include "terminal.h"
#include "screen.h"

int main(int argc, char** argv) {
	enable_raw_mode();
	init_config();
	if(argc >= 2) {
		editor_open(argv[1]);
	}

	atexit(disable_raw_mode);

	while(true) {
		draw_screen();
		process_keypress();
	}
	return EXIT_SUCCESS;
}


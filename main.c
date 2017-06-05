#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "keyboard.h"
#include "process.h"
#include "terminal.h"
#include "screen.h"

int main() {
	enable_raw_mode();
	init_config();
	atexit(disable_raw_mode);

	while(true) {
		draw_screen();
		process_keypress();
	}
	return EXIT_SUCCESS;
}


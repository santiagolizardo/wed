#include "process.h"

#include <stdio.h>
#include <stdlib.h>

#include "screen.h"

void exit_error(const char *s) {
	clear_screen();

	perror(s);
	exit(EXIT_FAILURE);
}



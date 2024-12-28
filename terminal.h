#pragma once

#include <stddef.h>
#include <termios.h>

typedef struct line_t {
	size_t size;
	char *chars;
} line_t;

struct config_t {
	int cursor_x, cursor_y;
	int num_rows, num_cols;
	int num_lines;
	line_t* line;
	struct termios orig_termios;
};

void init_config();

void enable_raw_mode();
void disable_raw_mode();
void editor_open(const char* filename);


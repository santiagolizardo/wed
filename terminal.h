#pragma once

#include <termios.h>

struct config_t {
	int num_rows, num_cols;
	struct termios orig_termios;
};

struct config_t config;

void init_config();

void enable_raw_mode();
void disable_raw_mode();


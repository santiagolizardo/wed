#pragma once

#include <stdbool.h>

#include "terminal.h"
#include "buffer.h"

extern struct config_t config;

void clear_screen();
void draw_screen();

bool obtain_window_size(int* rows, int* cols);


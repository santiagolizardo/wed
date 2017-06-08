#pragma once

#define CTRL_KEY(k) ((k) & 0x1f)

int read_key();
void process_keypress();


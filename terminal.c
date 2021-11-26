#include "terminal.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "screen.h"

struct config_t config;

void init_config() {
	config.cursor_x = config.cursor_y = 0;
	config.num_lines = 0;
	config.line = NULL;

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

void editor_append_line(char* s, size_t len) {
	config.line = realloc(config.line, sizeof(line_t) * (config.num_lines + 1));

	int at = config.num_lines;
	config.line[at].size = len;
	config.line[at].chars = malloc(len + 1);
	memcpy(config.line[at].chars, s, len);
	config.line[at].chars[len] = '\0';

	config.num_lines++;
}

void editor_open(const char* filename) {
	FILE* fp = fopen(filename, "r");
	if(!fp) {
		exit_error("fopen");
	}
	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_len;
	while((line_len = getline(&line, &line_cap, fp)) != -1) {
		while(line_len > 0 && (line[line_len - 1] == 'n' || line[line_len - 1] == '\r')) {
				line_len--;
		}
		editor_append_line(line, line_len);
	}
	free(line);
	fclose(fp);
}



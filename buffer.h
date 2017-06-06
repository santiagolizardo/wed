#pragma once

struct buffer_t {
	char *d;
	int len;
};

#define BUFFER_INIT {NULL, 0}

void buffer_append(struct buffer_t* buffer, const char* s, int len);
void buffer_free(struct buffer_t* buffer);


#pragma once
#include <stdio.h>

struct buffer_t {
	char *d;
	size_t len;
};

#define BUFFER_INIT {NULL, 0}

void buffer_append(struct buffer_t* buffer, const char* s, size_t len);
void buffer_free(const struct buffer_t* buffer);


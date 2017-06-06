#include "buffer.h"

#include <stdlib.h>
#include <string.h>

void buffer_append(struct buffer_t* buffer, const char* s, int len) {
	char *new = realloc(buffer->d, buffer->len + len);

	if(new == NULL) {
		return;
	}

	memcpy(&new[buffer->len], s, len);
	buffer->d = new;
	buffer->len += len;
}

void buffer_free(struct buffer_t* buffer) {
	free(buffer->d);
}


CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11 -g -D_POSIX_C_SOURCE=200809L
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
PROGRAM=wed

all: $(PROGRAM)

$(PROGRAM): $(OBJS) 
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f wed 


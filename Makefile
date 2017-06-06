CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -g
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

wed: $(OBJS) 
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f wed 


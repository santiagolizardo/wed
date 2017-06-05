CC=gcc
CFLAGS=-Wall -pedantic -std=c11

wed: screen.o keyboard.o terminal.o process.o main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f wed 


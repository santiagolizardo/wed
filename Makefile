
wed: main.c
	$(CC) $< -o $@ -Wall -pedantic -std=c11

clean:
	rm wed 


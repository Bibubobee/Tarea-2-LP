CC=gcc
CFLAGS=-Wall -g
simulacion: simulacion.c Animal.c
	$(CC) $(CFLAGS) -o simulacion simulacion.c Animal.c

Animal.c: Animal.h
	$(CC) $(CFLAGS )-c Animalh.o Animal.h	

.PHONY: clean
clean:
	rm -rf *.o
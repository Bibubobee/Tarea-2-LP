CC=gcc
CFLAGS=-Wall -g
simulacion: simulacion.c
	$(CC) $(CFLAGS) -o simulacion simulacion.c

simulacion.o: Animal.c
	$(CC) $(CFLAGS )-c Animal.o Animal.c

Animal.c: Animal.h
	$(CC) $(CFLAGS )-c Animalh.o Animal.h	

.PHONY: clean
clean:
	rm -rf *.o
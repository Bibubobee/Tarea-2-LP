CC=gcc
CFLAGS=-Wall -g
exec: Animal.o Mundo.o simulacion.o
	$(CC) $(CFLAGS) -o exec Animal.o Mundo.o simulacion.o -lm

simulacion.o: simulacion.c
	$(CC) $(CFLAGS) -c simulacion.c

Animal.o: Animal.c Animal.h
	$(CC) $(CFLAGS) -c Animal.c

Mundo.o: Mundo.c Mundo.h
	$(CC) $(CFLAGS) -c Mundo.c

.PHONY: clean
clean:
	rm -rf *.o exec
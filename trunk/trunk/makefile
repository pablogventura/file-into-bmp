CC = gcc
CFLAGS = -ansi -pedantic -Wall -std=c99 -g
OBJECTS = main.o simplebmp.o



main : $(OBJECTS)
		$(CC) $(OBJECTS) -o f2bmp $(CFLAGS)
		
		
main.o: main.c simplebmp.h
		$(CC) -c $(CFLAGS) main.c
		
		
simplebmp.o: simplebmp.c simplebmp.h
		$(CC) -c $(CFLAGS) simplebmp.c
		
clean:
		rm -f f2bmp *.o *.ghc *~

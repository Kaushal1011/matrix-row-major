
CC = gcc
CFLAGS = -std=c11 -g

main.out: main.o matrix.o nullspace.o
	$(CC) $(CFLAGS) *.o -o main.out

main.o: main.c matrix.h pch.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h pch.h
	$(CC) $(CFLAGS) -c matrix.c

nullspace.o: nullspace.c matrix.h
	$(CC) $(CFLAGS) -c nullspace.c

clean:
	del matrix.o
	del main.o
	del nullspace.o
	del main.out

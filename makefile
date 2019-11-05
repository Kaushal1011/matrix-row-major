

CFLAGS = -std=c11 -g

main.out: main.o matrix.o nullspace.o solve.o regression.o
	$(CC) $(CFLAGS) main.o matrix.o nullspace.o solve.o regression.o -o main.out -lm

main.o: main.c matrix.h pch.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h pch.h
	$(CC) $(CFLAGS) -c matrix.c -lm

nullspace.o: nullspace.c matrix.h pch.h
	$(CC) $(CFLAGS) -c nullspace.c

regression.o: regression.c matrix.h pch.h
	$(CC) $(CFLAGS) -c regression.c -lm

solve.o: solve.c matrix.h pch.h
	$(CC) $(CFLAGS) -c solve.c

clean:
	rm *.o  main.out

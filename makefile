all: ctoe

ctoe: ctoe.o
	gcc ctoe.o -o ctoe

ctoe.o: ctoe.c
	gcc -c ctoe.c

clean:
	rm ctoe *.o
CC = gcc
CFLAG = -Wall -std=c11 -g -c
FLAG = -Wall -std=c11
all:
	$(CC) $(CFLAG) src/LinkedListAPI.c -o bin/llist.o -Iinclude
	$(CC) $(CFLAG) src/VCardParser.c -o bin/cparse.o -Iinclude
	ar cr bin/libllist.a bin/llist.o
	ar cr bin/libcparse.a bin/cparse.o
list:
	$(CC) $(CFLAG) src/LinkedListAPI.c -o llist.o -Iinclude
	ar cr bin/libllist.a llist.o
parser:

	$(CC) $(CFLAG) src/VCardParser.c -o cparse.o -Iinclude
	ar cr bin/libcparse.a cparse.o

clean:
	rm -f bin/*.o bin/*.a
	rm -f *.o

all: liblist.so test

test: test.c liblist.so
	gcc test.c -o test -llist

liblist.so: list.c list.h
	gcc -shared -fPIC -Wall -Wextra list.c -o liblist.so

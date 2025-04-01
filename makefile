CFLAGS=-Wall -Wextra
CC=gcc
OBJS=obj/list.o obj/map.o

all: setup $(OBJS)
	gcc -shared -fPIC $(CFLAGS) $(OBJS) -o ~/Desktop/programming/bin/libcutils.so

setup:
	mkdir -p obj
	mkdir -p ~/Desktop/programming/include/cutils/

obj/list.o: list/list.c list/list.h
	cp list/list.h ~/Desktop/programming/include/cutils/
	gcc -c -fPIC $(CFLAGS) list/list.c -o obj/list.o

obj/map.o: map/map.o map/map.h
	cp map/map.h ~/Desktop/programming/include/cutils/
	gcc -c -fPIC $(CFLAGS) map/map.c -o obj/map.o

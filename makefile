CFLAGS=-Wall -Wextra
CC=gcc
OBJS=obj/list.o obj/map.o

all: $(OBJS)
	gcc -shared -fPIC $(CFLAGS) $(OBJS) -o ~/cutils/bin/libcutils.so

obj/list.o: list/list.c list/list.h
	cp list/list.h ~/cutils/include/cutils/
	gcc -c -fPIC $(CFLAGS) list/list.c -o obj/list.o

obj/map.o: map/map.o map/map.h
	cp map/map.h ~/cutils/include/cutils/
	gcc -c -fPIC $(CFLAGS) map/map.c -o obj/map.o

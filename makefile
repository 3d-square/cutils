CFLAGS=-Wall -Wextra
CC=gcc
OBJS=obj/list.o obj/map.o obj/sb.o

all: $(OBJS)
	gcc -shared -fPIC $(CFLAGS) $(OBJS) -o ~/cutils/bin/libcutils.so

obj/list.o: list/list.c list/list.h
	gcc -c -fPIC $(CFLAGS) list/list.c -o obj/list.o

obj/map.o: map/map.o map/map.h
	gcc -c -fPIC $(CFLAGS) map/map.c -o obj/map.o

obj/sb.o: sb/stringbuilder.c sb/stringbuilder.h
	gcc -c -fPIC $(CFLAGS) sb/stringbuilder.c -o obj/sb.o

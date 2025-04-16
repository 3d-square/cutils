#pragma once

#include <cutils/list.h>

#define MAPSIZE 17

typedef struct key_val{
   char *key;
   void *val;
} key_val;


typedef struct _map{
   list buckets[MAPSIZE];
   int size;
   void (*destruct)(void *);
} *map;

typedef struct _m_iter{
   map m;
   int bucket;
   list curr;
   int done;
   int finished;
} map_iter;

unsigned long hash(char *s);

map map_create(void (*destruct)(void *)); 

key_val *map_put(map m, char *key, void *val);

void *map_get(map m, char *key);

int map_contains(map m, char *key);

void map_destroy(map m);

int map_delete_key(map m, char *key);

void map_no_free(void *);

void map_free_key_val(map m, key_val *keyval);

// Iterable functions

map_iter map_create_iter(map m);
   
int map_has_next(map_iter *iter);

key_val *map_iter_data(map_iter *iter);

void map_iter_next(map_iter *iter);

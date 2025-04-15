#pragma once

#include <cutils/list.h>

#define MAPSIZE 17

typedef struct _set{
   list buckets[MAPSIZE];
   int size;
   void (*destruct)(void *);
   long (*hash)(void *);
   int (*cmp)(void *, void *);
} *set;

long hash(char *s);

set set_create(void (*destruct)(void *), long (*hash)(void *), int (*cmp)(void *, void *)); 

key_val *set_put(set m, char *val);

char *set_get(set m, char *val);

int set_contains(set m, char *val);

void set_destroy(set m);

int set_delete_key(set m, char *val);

void set_free_key_val(set m, char *val);

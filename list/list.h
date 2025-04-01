#pragma once
typedef struct _list{
   struct _list *next;
   struct _list *prev;
   void *val;
} *list;

typedef int (*list_comparator)(void *, void *);
typedef void (*list_free)(void *);

void *d2p(double d);
double p2d(void *p);
int list_int_cmp(void *, void *);
int list_double_cmp(void *, void *);
int list_str_cmp(void *, void *);

list list_insert(list head, void *val);
list list_delete(list head, int index, list_free del);
void *list_remove(list head, int index);
list list_delete_all(list head, list_free del);
int list_contains(list head, void *val, list_comparator cmp);

#pragma once
#include <stdlib.h>
#include <stdio.h>

#define array_struct(name, typ)\
typedef struct {\
   typ *array;\
   int size;\
   int length;\
} name;

#define array_get(arr, idx) (arr)->array[idx]

#define array_size(arr) (arr)->length
#define array_capacity(arr) (arr)->size

#define array_init(arr, sz)\
do{\
   (arr)->length = 0;\
   (arr)->size = sz;\
   (arr)->array = malloc(sz * sizeof((arr)->array[0]));\
} while(0);

#define array_append(arr, val)\
do{\
   if((arr)->length + 1 >= (arr)->size){\
      (arr)->size = (int)((arr)->size * 2.5);\
      (arr)->array = realloc((arr)->array, (arr)->size * sizeof((arr)->array[0]));\
   }\
   (arr)->array[(arr)->length++] = val;\
} while(0);

// #define array_get(arr, idx, ptr)\
// do{\
//    if((arr)->length < idx - 1){\
//       fprintf(stderr, "Index out of bounds\n");\
//       exit(1);\
//    }\
//    *ptr = (arr)->array[idx];\
// } while(0);

#define array_insert(arr, val, idx)\
do{\
   if((arr)->length + 1 >= (arr)->size){\
      (arr)->size = (int)((arr)->size * 1.5);\
      (arr)->array = realloc((arr)->array, (arr)->size * sizeof((arr)->array[0]));\
   }\
   if((arr)->length < idx || idx < -1){\
      fprintf(stderr, "Index out of bounds\n");\
      exit(1);\
   }\
\
   for(int _i = (arr)->length; _i > idx; --_i){\
      (arr)->array[_i] = (arr)->array[_i - 1];\
   }\
   (arr)->array[idx] = val;\
   (arr)->length++;\
} while(0);

#define array_remove(arr, idx, del_func)\
do{\
   if((arr)->length < idx || idx < -1){\
      fprintf(stderr, "Index out of bounds\n");\
      exit(1);\
   }\
\
   if(del_func != NULL){\
      del_func((arr)->array[idx]);\
   }\
   for(int _i = idx; _i < (arr)->length + 1; ++_i){\
      (arr)->array[_i] = (arr)->array[_i + 1];\
   }\
   (arr)->length--;\
} while(0);

#define array_delete(arr)\
do {\
   free((arr)->array);\
   (arr)->length = 0;\
   (arr)->size = 0;\
   (arr)->array = NULL;\
} while(0);

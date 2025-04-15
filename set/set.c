#include <cutils/map.h>
#include <cutils/list.h>
#include <string.h>
#include <stdlib.h>

#define node_get_val(node) (((key_val *)(node->val))->val)
#define node_get_key(node) (((key_val *)(node->val))->key)

long hash(char *s){
   long hashv = 5381;
   int c;
   
   while((c = *s++)){
      hashv = ((hashv << 5) + hashv) + c;
   }

   return hashv;
}

key_val *alloc_key_val(char *key, void *val){
   key_val *keyval = malloc(sizeof(key_val));
   keyval->key = strdup(key);
   keyval->val = val;
   return keyval;
}

map map_create(void (*destruct)(void *)){
   map m = calloc(1, sizeof(struct _map));
   if(destruct == NULL){
      m->destruct = map_no_free;
   }else{
      m->destruct = destruct;
   }
   return m;
}

int map_cmp(char *key, key_val *v2){
   return strcmp(key, v2->key);
}

key_val *map_put(map m, char *key, void *val){
   long hashv = hash(key) % MAPSIZE;

   if(m->buckets[hashv] == NULL){
      key_val *keyval = alloc_key_val(key, val);
      m->buckets[hashv] = list_insert(NULL, keyval);

      return keyval;
   }

   list prev;
   for(list curr = m->buckets[hashv]; curr; curr = curr->next){
      if(strcmp(key, node_get_key(curr)) == 0){
         m->destruct(node_get_val(curr));
         node_get_val(curr) = val;
         return (key_val *)curr->val;
      }
      prev = curr->prev;
   }

   key_val *keyval = alloc_key_val(key, val);
   
   list_insert(prev, keyval);

   return keyval;
}

void map_no_free(void *){

}

void delete_key_val(key_val *keyval){
   free(keyval->key);
   free(keyval);
}

int map_contains(map m, char *key){
   long hashv = hash(key) % MAPSIZE;

   return list_contains(m->buckets[hashv], key, (list_comparator)map_cmp);
}

void *map_get(map m, char *key){
   long hashv = hash(key) % MAPSIZE;
   
   list curr = m->buckets[hashv];

   while(curr){
      if(strcmp(key, node_get_val(curr))){
         return node_get_val(curr);
      }
      curr = curr->next;
   }

   return NULL;
}

void map_free_key_val(map m, key_val *keyval){
   free(keyval->key);
   if(m->destruct) m->destruct(keyval->val);
   free(keyval);
}

void map_destroy(map m){
   for(int i = 0; i < MAPSIZE; ++i){
      if(m->buckets[i]){
         list curr = m->buckets[i];
         while(curr){
            list next = curr->next;
            key_val *data = list_remove(curr, 0);
            map_free_key_val(m, data);
            curr = next;
         }
      }
   }
   free(m);
}

int map_delete_key(map m, char *key){
   long hashv = hash(key) % MAPSIZE;

   list curr;
   int i = 0;
   for(curr = m->buckets[hashv]; curr; curr = curr->next, i++){
      if(strcmp(key, ((key_val *)(curr->val))->key) == 0){
         key_val *data = list_remove(m->buckets[hashv], i);
         map_free_key_val(m, data);
         return 1;
      }
   }
   return 0;
}

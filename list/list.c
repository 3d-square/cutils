#include <cutils/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

void *d2p(double d){
   uint64_t tmp;

   memcpy(&tmp, &d, sizeof(double));

   return (void *)tmp;
}

double p2d(void *p){
   double tmp;

   memcpy(&tmp, &p, sizeof(double));

   return tmp;
}

int list_int_cmp(void *v1, void *v2){
   return (int)(v1 - v2);
}
int list_double_cmp(void *v1, void *v2){
   return (p2d(v1) - p2d(v2)) > 0.00000001;
}
int list_str_cmp(void *v1, void *v2){
   return strcmp((char *)v1, (char *)v2);
}

list list_insert(list head, void *val){
   list node = calloc(1, sizeof(*node));
   node->val = val;

   if(head == NULL){
      return node;
   }

   list curr = head;

   while(curr->next){
      curr = curr->next;
   }

   curr->next = node;

   return head;
}

list list_remove(list head, int index, void **data){
   list curr = head;
   *data = NULL;
   if(head == NULL){
      return NULL;
   }

   if(index == 0){
      list tmp = head;
      head = head->next;
      if(head){
         head->prev = NULL;
      }
      *data = tmp->val;
      free(tmp);
      return head;
   }

  while(index > 0 && curr){
      index--;
      curr = curr->next;
   }

   if(curr == NULL){
      return head;
   }

   if(curr->prev){
      curr->prev->next = curr->next;
   }

   if(curr->next){
      curr->next->prev = curr->prev;
   }

   *data = curr->val;
   free(curr);

   return head;
}

list list_delete(list head, int index, list_free del){
   list curr = head;
   
   if(head == NULL){
      return NULL;
   }

   if(index == 0){
      head = head->next;
   }

   while(index > 0 && curr){
      index--;
      curr = curr->next;
   }

   if(curr == NULL){
      return head;
   }

   if(curr->prev){
      curr->prev->next = curr->next;
   }

   if(curr->next){
      curr->next->prev = curr->prev;
   }

   if(del){
      del(curr->val);
   }
   free(curr);


   return head;
}

list list_delete_all(list head, list_free del){
   while(head){
      head = list_delete(head, 0, del);
   }

   return NULL;
}

int list_contains(list head, void *val, list_comparator cmp){
   while(head){
      if(cmp(val, head->val) == 0){
         return 1;
      }
      head = head->next;
   }

   return 0;
}

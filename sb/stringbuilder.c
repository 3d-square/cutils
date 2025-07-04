#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "stringbuilder.h"

#define pp(v) printf(#v " = %lu\n", v)

void sb_append_c(sb *builder, char c){
   assert(builder);
   assert(builder->string);

   // if(builder->size > 0 && builder->string[builder->size - 1] == 0){
   //    builder->size--;
   // }

   if(builder->size + 1 > builder->capacity){
      builder->string = realloc(builder->string, builder->capacity * 2);

      assert(builder->string);
      builder->capacity *= 2;
   }

   builder->string[(builder->size)++] = c;
}

void sb_insert_c(sb *builder, char c, size_t index){
   assert(builder);
   assert(builder->string);

   if(index > builder->size){
      fprintf(stderr, "Index Out Of Bounds\n");
      exit(1);
   }

   if(builder->size + 1 > builder->capacity){
      builder->string = realloc(builder->string, builder->capacity * 2);

      assert(builder->string);
      builder->capacity *= 2;
   }

   for(size_t i = builder->size; i > index && i <= builder->size; --i){
      builder->string[i] = builder->string[i - 1];
   }

   builder->string[index] = c;
   builder->size++;
}

void sb_append_s(sb *builder, char *s){
   assert(s);
   assert(builder->string);
   assert(strlen(s) > 0);

   if(builder->string[builder->size - 1] == 0){
      builder->size--;
   }

   size_t s_len = strlen(s);

   if(builder->size + s_len > builder->capacity){
      builder->string = realloc(builder->string, builder->capacity + s_len);

      assert(builder->string);
      builder->capacity += s_len;
   }

   strncat(builder->string, s, s_len);
   builder->size += s_len;
}

sb sb_from_str(char *s){
   sb builder;
   size_t s_len = strlen(s);
   size_t init_len = s_len > 8 ? s_len : 8;

   builder.string = malloc(init_len * sizeof(char) + 1);

   assert(builder.string);
   memset(builder.string, '\0', init_len - 1);

   strcpy(builder.string, s);
   builder.capacity = init_len;
   builder.size = s_len;

   return builder;
}

void sb_clear(sb *builder){
   assert(builder);
   builder->size = 0;
}

void sb_free(sb *builder){
   assert(builder);
   free(builder->string);
   builder->size = 0;
   builder->capacity = 0;
}

void sb_print(sb *builder){
   assert(builder);
   printf("'%.*s'\n", (int)builder->size, builder->string);
}

sb sb_get_word(const sb *builder, size_t start, char delim, size_t *spaceidx){
   
   assert(builder);
   assert(builder->string);
   assert(start < builder->size);
   size_t word_len = 0;

   if(delim == WHITESPACE){
      for(long unsigned  i = start; i < builder->size && !isspace(builder->string[i]); ++word_len, ++i);
   }else{
      for(long unsigned  i = start; i < builder->size && builder->string[i] != delim; ++word_len, ++i);
   }

   *spaceidx = start + word_len;

   sb word = {0};

   char *string = malloc(word_len);
   strncpy(string, builder->string + start, word_len);

   word.string = string;
   word.capacity = word_len;
   word.size = word_len;

   return word;
}

sb sb_substring(sb *builder, size_t start, size_t end){
   assert(builder);
   assert(builder->string);
   assert(start < builder->size);

   end = builder->size < end ? builder->size : end;
   size_t substr_len = end - start + 1;

   sb substr;

   substr.size = substr_len;
   substr.capacity = substr_len;

   char *string = malloc(substr_len * sizeof(char));

   strncpy(string, builder->string + start, substr_len);
   substr.string = string;

   return substr;
}

sb *sb_split(const sb *builder, char delim, size_t *length){
   assert(builder);
   assert(builder->string);

   size_t array_size = 0;

   for(size_t i = 0; i < builder->size; ++i){
      if(delim != WHITESPACE){
         if(builder->string[i] == delim) ++array_size;
      }else{
         if(isspace(builder->string[i])) ++array_size;
      }
   }

   sb *splitted = malloc((array_size + 1) * sizeof(sb));

   size_t next = 0;
   size_t index = 0;

   while(next < builder->size){
      splitted[index++] = sb_get_word(builder, next, delim, &next);
      ++next;
   }

   
   *length = index;

   return splitted;
   
}

void sb_concat(sb *s1, const sb *s2){
   assert(s1);
   assert(s1->string);
   assert(s2);
   assert(s2->string);

   if(s1->capacity <= s1->size + s2->size){
      // printf("reallocating...\n");
      s1->string = realloc(s1->string, sizeof(char) * (s1->capacity + s2->size));

      assert(s1->string);
      s1->capacity += s2->size;
   }

   // printf("%*s + %*s\n", (int)s1->size, s1->string, (int)s2->size, s2->string);

   strncpy(s1->string + s1->size, s2->string, s2->size); // Buffer is able to have all of s2 appended to it
   s1->size += s2->size;

   // printf("concated: %*s\n", (int)s1->size, s1->string);
}

void sb_free_list(sb *list, size_t length){
   assert(list);

   for(size_t i = 0; i < length; ++i){
      sb_free(&(list[i]));
   }

   free(list);

}

int sb_equal(sb *lhs, sb *rhs){
   if(lhs == rhs)
      return 1;

   if(lhs == NULL || rhs == NULL)
      return 0;

   if(lhs->string == rhs->string)
      return 1;

   if(lhs->size != rhs->size)
      return 0;

   return strncmp(lhs->string, rhs->string, lhs->size) == 0;
}


int sb_strequal(sb *builder, char *string, size_t size){
   if(builder == NULL)
      return 0;

   if(string == NULL)
      return 0;

   if(builder->size != size)
      return 0;

   return strncmp(builder->string, string, size) == 0;
}

const char *sb_to_cstr(sb *builder){
   assert(builder);

   if(builder->size >= builder->capacity - 1){
      builder->string = realloc(builder->string, builder->capacity + 1);
      assert(builder->string);
      builder->capacity += 1;
   }

   builder->string[builder->size] = '\0';
   return builder->string;
}

const char *sb_str(const sb *builder, char *buffer, size_t buffer_len){
   assert(builder);
   size_t copy_size = builder->size > buffer_len - 1 ? buffer_len : builder->size;
   strncpy(buffer, builder->string, copy_size);
   buffer[copy_size] = '\0';

   return buffer;
}

sb sb_read_file(const char *file_name){
   char buffer[128] = {0};
   FILE *file = fopen(file_name, "r");
   assert(file && "File unable to be opened");

   size_t length = 0;
   sb file_contents = sb_from_str("");

   while((length = fread(buffer, 1, 127, file)) != 0){
      sb_append_s(&file_contents, buffer);
      memset(buffer, '\0', 128);
   }

   fclose(file);

   return file_contents;
}

sb *sb_read_lines(const char *file_name, size_t *list_length){
   char buffer[128] = {0};
   FILE *file = fopen(file_name, "r");
   assert(file && "File unable to be opened");

   size_t length = 0;
   sb file_contents = sb_from_str("");

   while((length = fread(buffer, 1, 127, file)) != 0){
      sb_append_s(&file_contents, buffer);
      memset(buffer, '\0', 128);
   }

   sb *list = sb_split(&file_contents, '\n', list_length);
   
   sb_free(&file_contents);
   fclose(file);
   
   return list;
}

sb *sb_read_tokens(const char *file_name, size_t *list_length){
   char buffer[128] = {0};
   FILE *file = fopen(file_name, "r");
   assert(file && "File unable to be opened");

   size_t length = 0;
   sb file_contents = sb_from_str("");

   while((length = fread(buffer, 1, 127, file)) != 0){
      sb_append_s(&file_contents, buffer);
      memset(buffer, '\0', 128);
   }

   sb *list = sb_split(&file_contents, WHITESPACE, list_length);
   
   sb_free(&file_contents);
   fclose(file);

   return list;
}


long sb_indexof(const sb *builder, char c, size_t start){
   assert(builder);
   assert(builder->size);

   long index = -1;
   char *str = builder->string;

   if(start < builder->size){
      for(size_t i = start; i < builder->size; ++i){
         if(*str == c){
            index = i;
            break;
         }
         ++str;
      }
   }
   return index;
}

void sb_remove_c(sb *builder, size_t index){
   assert(builder);
   assert(builder->string);

   if(index > builder->size){
      fprintf(stderr, "Index Out Of Bounds ");
      fprintf(stderr, "index = %lu, size = %lu\n", index, builder->size);
      exit(1);
   }

   for(size_t i = index; i < builder->size; ++i){
      builder->string[i] = builder->string[i + 1];
   }

   builder->size--;
}

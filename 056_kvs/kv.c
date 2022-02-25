#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname){
  kvarray_t * kv_array = malloc(sizeof(* kv_array));
  kv_array->pairs = NULL;
  kv_array->len = 0;

  FILE * f = fopen(fname, "r");
  assert(f != NULL);
  size_t sz = 0;
  char * line = NULL;
  size_t i = 0;
  while(getline(&line, &sz, f) >= 0){
    kv_array->len++;
    i = kv_array->len - 1;
    kv_array->pairs = realloc(kv_array->pairs, kv_array->len * sizeof(* kv_array->pairs));
    kv_array->pairs[i] = malloc(sizeof(* kv_array->pairs[i]));
    //kv_array->pairs[i]->key = malloc(sizeof(* kv_array->pairs[i]->key));
    //kv_array->pairs[i]->value = malloc(sizeof(* kv_array->pairs[i]->value));

    char * equal = strchr(line, '=');
    assert(equal != NULL);
    * equal = '\0';
    kv_array->pairs[i]->key = line;
    char * end = strchr(equal + 1, '\n');
      if(end != NULL){
        * end = '\0';
        kv_array->pairs[i]->value = equal + 1;
      }
      else{
        kv_array->pairs[i]->value =  NULL;
      }
    line = NULL;
  }
  free(line);

  if(fclose(f) == 0) {
      return kv_array;
  }
  else {
      return NULL;
  }
}

void freeKVs(kvarray_t * pairs) {
  for(size_t i = 0; i < pairs->len; i++){
      free(pairs->pairs[i]->key);
      //free(pairs->pairs[i]->value);
      free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}


void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->len; i++){
      printf("key = '%s' value = '%s'\n", pairs->pairs[i]->key, pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->len; i++) {
    if (!strcmp(key, (pairs->pairs[i])->key)) {
      return (pairs->pairs[i])->value;
    }
  }
  return NULL;
}

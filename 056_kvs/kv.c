#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * kv_array = malloc(sizeof(* kv_array));
  kv_array->pair = malloc(sizeof(* kv_array->pair));
  kv_array->len = 0;

  char * line = NULL;
  size_t sz = 0;
  FILE * f =fopen(fname, "r");
  size_t len = 0;

  while((len = (getline(&line, &sz, f)) >= 0)){
    kv_array->len++;
    kv_array->pair = realloc(kv_array->pair, len * sizeof(* kv_array->pair));
    char * equal = strchr(line, '=');
    size_t key_len = equal - line;
    kv_array->pair->key = strndup(line, key_len);

    char * next = strchr(equal + 1, '\n');
    if (next != NULL) {
      size_t value_len = next - equal - 1;
      kv_array->pair[kv_array->len - 1].value = strndup(equal + 1, value_len);
    }
    else {
      kv_array->pair[kv_array->len - 1].value = strdup(equal + 1);
    }

    free(line);
    line = NULL;
  }
  free(line);

  return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    free((pairs->pair + i)->key);
    free((pairs->pair + i)->value);
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pair[i].key, pairs->pair[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    if (strcmp(key, pairs->pair[i].key) == 0) {
      return pairs->pair[i].value;
    }
  }
  return NULL;
}

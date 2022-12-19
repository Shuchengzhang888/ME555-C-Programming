#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * array = malloc(sizeof(*array));
  //array->type = malloc(sizeof(*array->type));
  array->type = NULL;
  array->len = 0;
  array->times_unknown = 0;
  return array;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //Unknown situation
  if (name == NULL){
      c->times_unknown ++;
      return;
  }
  //If name already exists
  for (size_t i = 0; i < c->len; i++){
      //if string1 is equal to string2, strcmp will return 0;
      if(strcmp(c->type[i]->value, name) == 0){
          c->type[i]->times ++;
          return;
      }
  }
  //Create new
  c->len ++;
  c->type = realloc(c->type, c->len * sizeof(*c->type));
  c->type[c->len - 1] = malloc(sizeof(*c->type[c->len - 1]));
  c->type[c->len - 1]->value = malloc(sizeof(strlen(name) + 1));
  int i = 0;
  while(*name!= '\0'){
      c->type[c->len - 1]->value[i] = *name;
      name ++;
      i ++;
  }
  c->type[c->len - 1]->value[i] = '\0';
  c->type[c->len - 1]->times = 1;
  return;                                                                                                                                        
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++){
      fprintf(outFile, "%s: %zu\n", c->type[i]->value, c->type[i]->times);
  }
  if(c->times_unknown != 0){
      fprintf(outFile, "<unknown> : %zu\n", c->times_unknown);
  }                                                                                                                                          
}
void freeCounts(counts_t * c) {
  //WRITE ME                                                                                                                                          
  for (size_t i = 0; i < c->len; i++){
      free(c->type[i]->value);
      free(c->type[i]);
  }
  free(c->type);
  free(c);
}


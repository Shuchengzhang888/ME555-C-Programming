#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->array = NULL;
  c->size = 0;
  c->cnt_unknown = 0;
  c->array = NULL;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->cnt_unknown++;
    return;
  }
  int i = 0;
  for (i = 0; i < c->size; i++) {
    if (strcmp(name, c->array[i]->string) == 0) {  //name existed.
      c->array[i]->cnt++;
      return;
    }
  }
  c->array = realloc(c->array, (c->size + 1) * sizeof(*c->array));
  c->array[c->size] = malloc(sizeof(*c->array[c->size]));
  //c->array[c->size]->string = name;
  const char * p = name;
  c->array[c->size]->string = malloc(strlen(name) + 1);  //
  i = 0;
  while (*p != '\0') {
    c->array[c->size]->string[i++] = *p;
    p++;
  }
  c->array[c->size]->string[i] = '\0';

  c->array[c->size]->cnt = 1;
  c->size++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->array[i]->string, c->array[i]->cnt);
  }
  if (c->cnt_unknown != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->cnt_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->array[i]->string);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * c = createCounts();
  char * key = NULL;
  size_t sz = 0;
  FILE * f = fopen(filename, "r");
  while (getline(&key, &sz, f) >= 0) {
    char * p = key;
    while (*p != '\n') {
      p++;
    }
    *p = '\0';

    //printf("k: %s\n", key);
    char * value = lookupValue(kvPairs, key);
    // printf("v: %s\n", value);
    addCount(c, value);
    //key = NULL;
  }
  free(key);
  if (fclose(f)) {
    perror("Cannot close the file.\n");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc == 1 || argc == 2) {
    perror("Wrong number of arguments!\n");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    if (f == NULL) {
      perror("Cannot open this file.\n");
      exit(EXIT_FAILURE);
    }
    printCounts(c, f);
    //close f
    if (fclose(f)) {
      perror("Cannot close the file.\n");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}

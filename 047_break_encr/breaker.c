#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define size 26

int findMax(int * freq, int n){
  int maxIndex = 0;
  for (int i = 0; i < n; i++){
    if (freq[i] > freq[maxIndex]){
        maxIndex = i;
    }
  }
  return maxIndex;
}

int decrypt(FILE *f){
  int c;
  int freq[size] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      freq[c - 'a'] += 1;
    }
  }
  int key = findMax(freq, size) + 'a' - 'e';
  if (key < 0){
    key = key + size;
  }
  
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int key = decrypt(f);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  if (key < 0 || key >= 26) {
    fprintf(stderr, "Key is not the correct range.\n");
    return EXIT_FAILURE;
  }
  printf("%d\n", key);

  return EXIT_SUCCESS;
}

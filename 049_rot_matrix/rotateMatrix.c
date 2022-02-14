#include<stdlib.h>
#include<stdio.h>

void rotate(FILE *f){
  int c;
  int i = 0, j = 0;
  int matrix[10][10];
  
  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      if (i >= 10) {
        perror("wrong number of row");
       
      }
      matrix[j++][10 - i - 1] = c;
    }
    else {
      if (j != 10) {
        perror("wrong number of col");
      }
      i++;
      j = 0;
    }
  }
  if (i < 10) {
    perror("wrong number of row");
  }
  
  i = 0;
  j = 0;
  
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
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
  
  rotate(f);
  
  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  
 
  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void toArray(FILE *f){
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  int cou = 0;
  char ** array =NULL;
  while((len = getline(&line, &sz, f)) != EOF){
      cou++;
      array = realloc(array, cou * sizeof(*array));
      array[cou-1] = line;
      line = NULL;
      sz = 0;
  }
  sortData(array,cou);
  for (int i = 0; i < cou; i++ ){
    fprintf(stdout, "%s", array[i]);
    free(array[i]);
  }
  free(array);
  free(line);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1){
    toArray(stdin);
  }
  else{
    for (int i = 1; i < argc; i++){
      FILE *f = fopen(argv[i],"r");
      if (f == NULL){
        fprintf(stderr,"Can not open file");
        exit(EXIT_FAILURE);
      }
      toArray(f);
      if(fclose(f)){
        fprintf(stderr,"Fail to close file");
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}

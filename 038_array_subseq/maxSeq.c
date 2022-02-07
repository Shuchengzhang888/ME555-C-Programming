#include <stdlib.h>
#include <stdio.h>

size_t  maxSeq(int * array, size_t n){
  if (n == 0){
    return 0;
  }
  else{
    int num = 1;
    int numFixed =1;

    for (size_t  i = 1; i < n; i++){
      if (array[i-1] < array[i]){
	num++;
      }
      else{
	numFixed = num;
	num = 1;
      }
    }

    if (num < numFixed){
      num = numFixed;
    }

    return num;
  }
}

#include <stdlib.h>
#include <stdio.h>

size_t  maxSeq(int * array, size_t n);

int test(int * array, size_t n, size_t expected_ans){
  size_t ans = maxSeq(array, n);

  for (int i = 0; i < n; i++){
    printf("%d ",array[i]);
  }
  printf("\n");
  
  if (ans == expected_ans){
    printf("Test succeed, the length fo the array is %ld\n", ans);
    return EXIT_SUCCESS;
  }
  else{
    printf("Test fail, your answer is %ld, expected answer is %ld\n", ans, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main (){
  int array1[] = {1, 2, 3, 4, 5};
  int array2[] = {5, 4, 3, 2, 1};
  int array3[] = {1, 2, 1, 3, 4};
  int array4[] = {-3, -5, -2, -1, 0};
  int array5[] = {1, 1, 1, 1, 1};
  int array6[] = {-6, -1, 0, 3, 99,};
  //int array7[] = {}; 
  test(array1, 5, 5);
  test(array2, 5, 1);
  test(array3, 5, 3);
  test(array4, 5, 4);
  test(array5, 5, 1);
  test(array6, 5, 5);
  //test(array7, 0, 0);
  return 0;
}

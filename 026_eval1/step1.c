//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write print_seq1_range
//  Step 1 (D): add test cases to main to test print_seq1_range
// 
// Be sure to #include any header files you need!
#include<stdio.h>
#include<stdlib.h>

int seq1(int x){
  return 3 * x -5;
}
void print_seq1_range(int low, int high){
  if(low < high){
    for(;low < high - 1; low++){
      printf("%d, ", seq1(low));
    }
    printf("%d\n", seq1(low));
  }
  else{
    printf("\n");
  }
}


int main(){
  int c1 = -5;
  int c2 = -1;
  int c3 = 0;
  int c4 = 1;
  int c5 = 10;
  printf("seq1(%d) = %d\n", c1, seq1(c1));
  printf("seq1(%d) = %d\n", c2, seq1(c2));
  printf("seq1(%d) = %d\n", c3, seq1(c3));
  printf("seq1(%d) = %d\n", c4, seq1(c4));
  printf("seq1(%d) = %d\n", c5, seq1(c5));


  printf("print_seq1_range(%d, %d)\n", c1,c2);
  print_seq1_range(c1, c2);
  printf("print_seq1_range(%d, %d)\n", c1,c3);
  print_seq1_range(c1, c3);
  printf("print_seq1_range(%d, %d)\n", c1,c4);
  print_seq1_range(c1, c4);
  printf("print_seq1_range(%d, %d)\n", c3,c5);
  print_seq1_range(c3, c5);
  printf("print_seq1_range(%d, %d)\n", c4,c5);
  print_seq1_range(c4, c5);
  printf("print_seq1_range(%d, %d)\n", c3,c3);
  print_seq1_range(c3, c3);
  printf("print_seq1_range(%d, %d)\n", c2,c1);
  print_seq1_range(c2, c1);
  printf("print_seq1_range(%d, %d)\n", c5,c4);
  print_seq1_range(c5, c4);
  return 0;
}


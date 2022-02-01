//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write count_neg_seq3_range
//  Step 3 (D): add test cases to main to test count_neg_seq3_range
// 
// Be sure to #include any header files you need!
#include<stdlib.h>
#include<stdio.h>


int seq3(int x, int y){
  return (y + 4)*(x - 1) + 3;
}



int count_neg_seq3_range(int xLow, int xHi, int yLow, int yHi){
  int count = 0;
  int yLow_org = yLow;
  if (xLow <= xHi && yLow <= yHi){
    for (;xLow < xHi; xLow++){
      for (;yLow < yHi; yLow++){
	if (seq3(xLow, yLow) < 0){
	  count ++;
	}
	
    }
      yLow = yLow_org;
  }
  }
  return count;
}

int main(){
  printf("seq3(%d, %d) = %d\n", 5, -5, seq3(5, -5));
  printf("seq3(%d, %d) = %d\n", 5, 5, seq3(5, 5));
  printf("seq3(%d, %d) = %d\n", -5, -5, seq3(-5, -5));
  printf("seq3(%d, %d) = %d\n", -5, 5, seq3(-5, 5));
  printf("seq3(%d, %d) = %d\n", 1, -4, seq3(1, -4));
  printf("seq3(%d, %d) = %d\n", 5, -4, seq3(5, -4));
  printf("seq3(%d, %d) = %d\n", -5, -4, seq3(-5, -4));
  printf("seq3(%d, %d) = %d\n", 1, -5, seq3(1, -5));
  printf("seq3(%d, %d) = %d\n", 1, 5, seq3(1, 5));
  printf("seq3(%d, %d) = %d\n", 8, -8, seq3(8, -8));
  printf("seq3(%d, %d) = %d\n", 8, 8, seq3(8, 8));
  printf("seq3(%d, %d) = %d\n", -8, -8, seq3(-8, -8));
  printf("seq3(%d, %d) = %d\n", -8, 8, seq3(-8, 8));

  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, count_neg_seq3_range(0, 2, 0, 3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -2, 2, -3, 3, count_neg_seq3_range(-2, 2, -3, 3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 2, 5, -2, 2, count_neg_seq3_range(2, 5, -2, 2));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -5, -3, 1, 3, count_neg_seq3_range(-5, -3, 1, 3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 0, count_neg_seq3_range(0, 0, 0, 0));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -8, -6, 6, 8, count_neg_seq3_range(-8, -6, 6, 8));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 2, 0, 0, 3, count_neg_seq3_range(2, 0, 0, 3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 0, 2, 3, 0, count_neg_seq3_range(0, 2, 3, 0));

  return 0;
}



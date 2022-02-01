//This file is for Step 2.
//You should do 
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sum_seq2
//  Step 2 (D): add test cases to main to test sum_seq2
// 
// Be sure to #include any header files you need!
#include<stdlib.h>
#include<stdio.h>

int seq2(int x){
  int ans = -2;
  int odd = 1;
  if(x >= 2){
    for (int i = 2; i < x; i++){
      ans += odd;
      odd += 2;
    }
  }
  else{
    for (int i = 2; i > x; i--){
      ans += odd;
      odd += 2;
    }
  }
  return ans;
}
int sum_seq2(int low, int high){
  if(low <= high){
    int ans = 0;
    for (; low <high; low++){
      ans += seq2(low);
    }
    return ans;
  }     
  else{
    return 0;
  }
}


int main(){
  int c1 = -5;
  int c2 = -1;
  int c3 = 2;
  int c4 = 5;
  int c5 = 14;
  printf("seq2(%d) = %d\n", c1, seq2(c1));
  printf("seq2(%d) = %d\n", c2, seq2(c2));
  printf("seq2(%d) = %d\n", c3, seq2(c3));
  printf("seq2(%d) = %d\n", c4, seq2(c4));
  printf("seq2(%d) = %d\n", c5, seq2(c5));


  printf("sum_seq2(%d, %d) = %d\n", c1, c2, sum_seq2(c1,c2));
  printf("sum_seq2(%d, %d) = %d\n", c1, c3, sum_seq2(c1,c3));
  printf("sum_seq2(%d, %d) = %d\n", c2, c4, sum_seq2(c2,c4));
  printf("sum_seq2(%d, %d) = %d\n", c3, c5, sum_seq2(c3,c5));
  printf("sum_seq2(%d, %d) = %d\n", c1, c5, sum_seq2(c1,c5));
  printf("sum_seq2(%d, %d) = %d\n", c4, c5, sum_seq2(c4,c5));
  printf("sum_seq2(%d, %d) = %d\n", c4, c4, sum_seq2(c4,c4));
  printf("sum_seq2(%d, %d) = %d\n", c2, c1, sum_seq2(c2,c1));
  printf("sum_seq2(%d, %d) = %d\n", c5, c4, sum_seq2(c5,c4));
  return 0;
}

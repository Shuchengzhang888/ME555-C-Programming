#include <stdio.h>
#include <stdlib.h>


unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    printf("x=%d, y=%d, answer is %d, Right.\n", x, y, expected_ans);
    return EXIT_SUCCESS;
  }
  printf("x=%d, y=%d, your answer is %d, Wrong.\n", x, y, ans);
  exit(EXIT_FAILURE);
}

int main(void) {
  run_check(0, 0, 1);
  run_check(3, 1, 3);
  run_check(3, 3, 27);
  run_check(2, 0, 1);
  run_check(1, 2, 1);
  run_check(-1, 2, 1);
  run_check(-1, 3, -1);
  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y) {
  unsigned ans = 1;
  if (y <= 0) {
    return ans;
  }
  return x * power(x, y - 1);
}

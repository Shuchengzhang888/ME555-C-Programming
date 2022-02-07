#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0)
    return 0;
  size_t cnt = 0, num = 0;
  for (size_t i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) {
      cnt += 1;
    }
    else {
      if (num < cnt) {
        num = cnt;
      }
      cnt = 0;
    }
  }
  if (num < cnt) {
    num = cnt;
  }
  return num + 1;
}

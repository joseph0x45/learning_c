#include <math.h>
#include <stdint.h>
#include <stdio.h>

uint16_t square_root(int number) {
  if (number < 0) {
    return -1;
  }
  if (number == 0) {
    return 0;
  }
  double precision = 0.001;
  double root = (double)number / 2;
  for (;;) {
    double temp_root = 0.5 * (root + (double)number / root);
    if (fabs(temp_root - root) < precision) {
      break;
    }
    root = temp_root;
  }
  return root;
}

int main() {
  uint16_t root = square_root(0);
  printf("%d\n", root);
  return 0;
}

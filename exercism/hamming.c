#include <stdio.h>
#include <string.h>
int compute(const char *lhs, const char *rhs) {
  if (!lhs || !rhs) {
    return -1;
  }
  if (strlen(lhs) != strlen(rhs)) {
    return -1;
  }
  int differences = 0;
  for (size_t i = 0; i < strlen(lhs); i++) {
    if (lhs[i] != rhs[i]) {
      ++differences;
    }
  }
  return differences;
}

int main() {
  int differences = compute("GAGCCTACTAACGGGAT", "CATCGTAATGACGGCCT");
  printf("They have %d differences\n", differences);
  return 0;
}

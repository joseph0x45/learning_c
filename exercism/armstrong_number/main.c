#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_armstrong_number(int candidate) {
  char candidate_str[20];
  sprintf(candidate_str, "%d", candidate);
  int sum = 0;
  int len = 0;
  while (candidate_str[len] != '\0') {
    ++len;
  }
  for (int i = 0; i < len; i++) {
    sum += pow(candidate_str[i] - '0', len);
  }
  return sum == candidate;
}

int main(int argc, char *argv[]) {
  bool result = is_armstrong_number(153);
  return EXIT_SUCCESS;
}

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int num_digits(int num) {
  int count = 0;
  while (num != 0) {
    count++;
    num /= 10;
  }
  return count;
}

bool is_armstrong_number(int candidate) {
  int len = num_digits(candidate);
  char candidate_str[len + 1];
  sprintf(candidate_str, "%d", candidate);
  int sum = 0;
  while (candidate_str[len] != '\0') {
    ++len;
  }
  for (int i = 0; i < len; i++) {
    sum += pow(candidate_str[i] - '0', len);
  }
  return sum == candidate;
}

int main(int argc, char *argv[]) {
  bool result = is_armstrong_number(9);
  printf("%d", result);
  return EXIT_SUCCESS;
}

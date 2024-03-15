#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }
  for (int i = 0; phrase[i] != '\0'; i++) {
    for (int j = i + 1; phrase[j] != '\0'; j++) {
      if (phrase[i] != '-' && phrase[i] != ' ') {
        if (tolower(phrase[i]) == tolower(phrase[j])) {
          return false;
        }
      }
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  bool result = is_isogram(NULL);
  printf("%d", result);
  return EXIT_SUCCESS;
}

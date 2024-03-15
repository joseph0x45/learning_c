#include <stdint.h>

uint64_t square(uint8_t index) {
  if (index == 0)
    return 0;
  uint64_t num_grains = 1;
  for (uint8_t i = 1; i < index; i++) {
    num_grains = 2 * num_grains;
  }
  return num_grains;
}

uint64_t total(void) {
  uint64_t total_grains = 0;
  for (int i = 1; i <= 64; i++) {
    total_grains += square(i);
  }
  return total_grains;
};

int main() {
  uint8_t result = square(6);
  uint64_t total_grains = total();
  return 0;
}

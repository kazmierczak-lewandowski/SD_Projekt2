#include "Utils.hpp"
void Utils::swap(int *a, int *b) {
  const int temp = *a;
  *a = *b;
  *b = temp;
}
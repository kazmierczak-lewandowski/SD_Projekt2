#include "Utils.hpp"
#include <algorithm>

int Utils::rng(const int min, const int max) {
  auto gen = getRandomGenerator();
  std::uniform_int_distribution dis(min, max);
  return dis(gen);
}
int Utils::gauss(const int min, const int max) {
  const double mean = (min + max) / 2.0;
  const double stddev = (max - min) / 6.0;

  auto gen = getRandomGenerator();
  std::normal_distribution dist(mean, stddev);
  double number = -1;
  do {
    number = dist(gen);
  } while (number < min || number > max);
  return static_cast<int>(number);
}
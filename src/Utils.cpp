#include "Utils.hpp"
#include <algorithm>

int Utils::rng(const int min, const int max) {
  static std::uniform_int_distribution<int> dist;
  auto& gen = get_generator();
  return dist(gen, std::uniform_int_distribution<>::param_type(min, max));
}

int Utils::gauss(const int min, const int max) {
  const double mean = (min + max) / 2.0;
  const double stddev = (max - min) / 6.0;
  static std::normal_distribution dist;
  auto& gen = get_generator();

  double number;
  do {
    number = dist(gen, std::normal_distribution<>::param_type(mean, stddev));
  } while (number < min || number > max);

  return static_cast<int>(std::round(number));
}
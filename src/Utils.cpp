#include "Utils.hpp"
int Utils::rng(const int min, const int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution dis(min, max);
  return dis(gen);
}
int Utils::gauss(const int min, const int max) {
  return std::midpoint(min, max); // Placeholder for Gaussian distribution
}
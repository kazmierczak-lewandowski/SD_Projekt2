#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

class Utils {
public:
  static int rng(int min, int max);
  static int gauss(int min, int max);

private:
  static std::mt19937& get_generator() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
  }
};

#endif // UTILS_HPP
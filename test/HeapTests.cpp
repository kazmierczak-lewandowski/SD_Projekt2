#include "../src/Heap.hpp"
#include <gtest/gtest.h>

TEST(HeapConstructorTests, DefaultCapacityConstructor) {
  const Heap heap{};
  EXPECT_EQ(heap.getSize(), 0);
}

TEST(HeapConstructorTests, ArrayConstructorWithExactCapacity) {
  std::vector inputArray = {3, 1, 4, 1, 5, 9};
  const auto capacity = static_cast<int>(inputArray.size());

  Heap heap(std::span(inputArray.data(), inputArray.size()), capacity);

  EXPECT_EQ(heap.getSize(), inputArray.size());
  EXPECT_EQ(heap.peek(), 9);
}

TEST(HeapConstructorTests, ArrayConstructorWithLargerCapacity) {

  std::vector inputArray = {3, 1, 4, 1, 5, 9};
  constexpr int capacity = 10;

  Heap heap(std::span(inputArray.data(), inputArray.size()), capacity);

  EXPECT_EQ(heap.getSize(), inputArray.size());
  EXPECT_EQ(heap.peek(), 9);
}

TEST(HeapConstructorTests, ArrayConstructorWithoutCapacity) {
  std::vector inputArray = {3, 1, 4, 1, 5, 9};

  Heap heap(std::span(inputArray.data(), inputArray.size()));

  EXPECT_EQ(heap.getSize(), inputArray.size());
  EXPECT_EQ(heap.peek(), 9);
}
TEST(HeapConstructorTests, ArrayConstructorWithCapacity) {
  std::vector inputArray = {3, 1, 4, 1, 5, 9};

  Heap heap(std::span(inputArray.data(), inputArray.size()), 100);

  EXPECT_EQ(heap.getSize(), inputArray.size());
  EXPECT_EQ(heap.peek(), 9);
}
#include "../src/Heap.hpp"
#include <gtest/gtest.h>
#include <vector>

bool isHeapValid(const Element *elements, const int size) {
  for (int i = 0; i < size; ++i) {
    const int left = 2 * i + 1;
    const int right = 2 * i + 2;
    if (left < size && elements[i] < elements[left]) {
      return false;
    }
    if (right < size && elements[i] < elements[right]) {
      return false;
    }
  }
  return true;
}
void add3ElementsForTests(Heap &heap) {
  heap.insert(Element{1, 10}, 10);
  heap.insert(Element{2, 20}, 20);
  heap.insert(Element{3, 5}, 5);
}
TEST(HeapTests, DefaultConstructor) {
  const Heap heap;
  EXPECT_EQ(heap.getHeight(), 0);
}

TEST(HeapTests, Insert) {
  Heap heap;
  add3ElementsForTests(heap);

  EXPECT_EQ(heap.peek().getPriority(), 20); // Max element
  EXPECT_TRUE(isHeapValid(heap.getElements(), heap.getSize()));
}

TEST(HeapTests, ExtractMax) {
  Heap heap;
  add3ElementsForTests(heap);

  const Element max = heap.extractMax();
  EXPECT_EQ(max.getPriority(), 20);
  EXPECT_TRUE(isHeapValid(heap.getElements(), heap.getSize()));
}

TEST(HeapTests, ConstructFromSpan) {
  std::vector<Element> elements = {{1, 10}, {2, 20}, {3, 5}};
  const Heap heap(elements);

  EXPECT_EQ(heap.peek().getPriority(), 20);
  EXPECT_TRUE(isHeapValid(heap.getElements(), heap.getSize()));
}

TEST(HeapTests, ModifyKey) {
  Heap heap;
  add3ElementsForTests(heap);

  heap.modifyKey(Element{1, 10}, 25);
  EXPECT_EQ(heap.peek().getPriority(), 25);
  EXPECT_TRUE(isHeapValid(heap.getElements(), heap.getSize()));
}

TEST(HeapTests, FindElement) {
  Heap heap;
  add3ElementsForTests(heap);

  const int index = heap.findElement(Element{3, 5}, 0);
  EXPECT_NE(index, -1);
  EXPECT_EQ(index, 2);
}

TEST(HeapTests, GetHeight) {
  Heap heap;
  add3ElementsForTests(heap);
  heap.insert(Element{4, 15}, 15);
  EXPECT_EQ(heap.getHeight(), 3);
}
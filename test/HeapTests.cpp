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
  heap.insert(Element{1, 10});
  heap.insert(Element{2, 20});
  heap.insert(Element{3, 5});
}
TEST(HeapTests, DefaultConstructor) {
  const Heap heap;
  EXPECT_EQ(heap.getHeight(), 0);
}

TEST(HeapTests, Insert) {
  Heap heap;
  add3ElementsForTests(heap);

  EXPECT_EQ(heap.peek().getPriority(), 20);
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

TEST(HeapTests, IncreaseKey) {
  Heap heap;
  add3ElementsForTests(heap);

  heap.modifyKey(Element{1, 10}, 25);
  EXPECT_EQ(heap.peek().getPriority(), 25);
  EXPECT_TRUE(isHeapValid(heap.getElements(), heap.getSize()));
}
TEST(HeapTests, DecreaseKey) {
  Heap heap;
  add3ElementsForTests(heap);

  heap.modifyKey(Element{1, 10}, 5);
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
  heap.insert(Element{4, 15});
  EXPECT_EQ(heap.getHeight(), 2);
}

TEST(HeapTests, GrowTest) {
  std::vector<Element> elements = {{1, 10}, {2, 20}, {3, 5}};
  Heap heap(elements);
  heap.insert(Element{4, 15});
  EXPECT_EQ(heap.getCapacity(), 6);
}

TEST(HeapTests, GetLevels) {
  std::vector<Element> elements = {{1, 10}, {2, 20}, {3, 5}, {4, 15}, {5, 25}};
  const Heap heap(elements);

  const std::vector<std::vector<Element>> levels = heap.getLevels();

  ASSERT_EQ(levels.size(), 3);

  EXPECT_EQ(levels[0].size(), 1);
  EXPECT_EQ(levels[0][0], elements[4]);

  EXPECT_EQ(levels[1].size(), 2);
  EXPECT_EQ(levels[1][0], elements[1]);
  EXPECT_EQ(levels[1][1], elements[2]);

  EXPECT_EQ(levels[2].size(), 2);
  EXPECT_EQ(levels[2][0], elements[3]);
  EXPECT_EQ(levels[2][1], elements[0]);
}
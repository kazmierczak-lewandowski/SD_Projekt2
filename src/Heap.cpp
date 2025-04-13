#include "Heap.hpp"
#include <cmath>
Heap::Heap() {
  elements = std::make_unique<int[]>(10);
  this->capacity = 10;
}
Heap::Heap(const std::span<int> arr, const int capacity) {
  this->capacity = capacity;
  this->elements = std::make_unique<int[]>(capacity);
  setSize(static_cast<int>(std::size(arr)));
  for (int i = 0; i < getSize(); ++i) {
    this->elements[i] = arr[i];
  }
  for (int i = getSize() / 2 - 1; i >= 0; --i) {
    heapify(i);
  }
}
std::vector<std::vector<int>> Heap::getLevels() const {
  std::vector<std::vector<int>> levels;
  for (int i = 1; i < getHeight(); i*=2) {
    std::vector<int> level;
    for (int j = 0; j < i; j++) {
      if (i + j >= getSize()) {
        break;
      }
      level.push_back(elements[i + j]);
    }
    levels.push_back(level);
  }
  return levels;
}
void Heap::insert(int value, int priority) {
  // Not implemented yet
}
int Heap::extractMax() {
  const int max = elements[0];
  elements[0] = elements[getSize() - 1];
  setSize(getSize() - 1);
  heapify(0);
  return max;
}
int Heap::peek() const { return elements[0]; }
void Heap::modifyKey(int value, int newPriority) {
  //Not implemented yet
}
int Heap::getHeight() const {
  return static_cast<int>(std::log2(getSize())) + 1;
}
void Heap::heapify(const int index) { // NOLINT(*-no-recursion)
  int largest = index;
  const int leftIndex = left(index);
  const int rightIndex = right(index);
  if (leftIndex < getSize() && elements[index] < elements[leftIndex]) {
    largest = left(index);
  }
  if (rightIndex < getSize() && elements[largest] < elements[rightIndex]) {
    largest = right(index);
  }
  if (largest != index) {
    std::swap(elements[index], elements[largest]);
    heapify(largest);
  }
}
int Heap::left(const int index) { return 2 * index + 1; }
int Heap::right(const int index) { return 2 * index + 2; }
int Heap::parent(const int index) { return (index - 1) / 2; }
void Heap::ensureCapacity() {
  if (capacity == getSize()) {
    grow();
  }
}
void Heap::grow() {
  auto newArr = std::make_unique<int[]>(getSize() * 2);
  for (long i = 0; i < getSize(); i++) {
    newArr[i] = elements[i];
  }
  elements = std::move(newArr);
  capacity = getSize() * 2;
}
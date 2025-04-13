#include "Heap.hpp"
Heap::Heap(const int capacity = 10) {
  elements = std::make_unique<int[]>(capacity);
  this->capacity = capacity;
}
Heap::Heap(const std::span<int> arr,
           const int capacity = static_cast<int>(std::size(arr))) {
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
void Heap::heapify(const int index) {
  int largest = index;
  if (elements[index] != -1 && elements[index] < elements[left(index)]) {
    largest = left(index);
  }
  if (elements[largest] != -1 && elements[largest] < elements[right(index)]) {
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
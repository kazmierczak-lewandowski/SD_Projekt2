#include "Heap.hpp"
#include <cmath>
Heap::Heap() {
  elements = std::make_unique<Element[]>(10);
  this->capacity = 10;
}
Heap::Heap(const std::span<Element> arr, const int capacity) {
  this->capacity = capacity;
  this->elements = std::make_unique<Element[]>(capacity);
  setSize(static_cast<int>(std::size(arr)));
  for (int i = 0; i < getSize(); ++i) {
    this->elements[i] = arr[i];
  }
  for (int i = getSize() / 2 - 1; i >= 0; --i) {
    heapifyDown(i);
  }
}
std::vector<std::vector<Element>> Heap::getLevels() const {
  std::vector<std::vector<Element>> levels;
  for (int i = 1; i < getHeight(); i *= 2) {
    std::vector<Element> level;
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
void Heap::insert(const Element element, int priority) {
  ensureCapacity();
  elements[getSize()] = element;
  heapifyUp(getSize());
  setSize(getSize() + 1);
}
Element Heap::extractMax() {
  const Element max = elements[0];
  elements[0] = elements[getSize() - 1];
  setSize(getSize() - 1);
  heapifyDown(0);
  return max;
}
int Heap::findElement(const Element &element, const int index) const {
  if (element == elements[index]) {
    return index;
  }
  if (left(index) < getSize()) {
    if (const int leftIndex = findElement(element, left(index));
        leftIndex != -1) {
      return leftIndex;
    }
  }
  if (right(index) < getSize()) {
    if (const int rightIndex = findElement(element, right(index));
        rightIndex != -1) {
      return rightIndex;
    }
  }
  return -1;
}
Element Heap::peek() const { return elements[0]; }
void Heap::modifyKey(const Element element, const int newPriority) {
  const int index = findElement(element, 0);
  if (index == -1) {
    return;
  }
  elements[index].setPriority(newPriority);
  if (elements[index].getPriority() > elements[parent(index)].getPriority()) {
    heapifyUp(index);
    return;
  }
  heapifyDown(index);
}
int Heap::getHeight() const {
  return static_cast<int>(std::log2(getSize())) + 1;
}
void Heap::heapifyDown(const int index) { // NOLINT(*-no-recursion)
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
    heapifyDown(largest);
  }
}
void Heap::heapifyUp(int index) {
  while (index > 0 && elements[parent(index)] < elements[index]) {
    std::swap(elements[index], elements[parent(index)]);
    index = parent(index);
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
  auto newArr = std::make_unique<Element[]>(getSize() * 2);
  for (long i = 0; i < getSize(); i++) {
    newArr[i] = elements[i];
  }
  elements = std::move(newArr);
  capacity = getSize() * 2;
}
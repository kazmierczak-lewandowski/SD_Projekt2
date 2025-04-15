#include "Heap.hpp"
#include <cmath>
std::vector<std::vector<Element>> Heap::getLevels() const {
  std::vector<std::vector<Element>> levels;
  const int size = getSize();
  if (size == 0)
    return levels;

  int levelNumber = 0;
  while (true) {
    const int start = static_cast<int>(std::pow(2, levelNumber)) - 1;
    if (start >= size)
      break;

    int end = static_cast<int>(std::pow(2, levelNumber + 1)) - 1;
    end = std::min(end, size);

    std::vector<Element> level;
    for (int i = start; i < end; i++) {
      level.push_back(elements[i]);
    }
    levels.push_back(level);
    levelNumber++;
  }
  return levels;
}
void Heap::insert(const Element element) {
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

int Heap::findElement(const Element &element, // NOLINT(*-no-recursion)
                      const int index) const {
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
void Heap::modifyKey(const Element &element, const int newPriority) {
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
void Heap::heapifyUp(const int index) {
  int currentIndex = index;
  while (currentIndex > 0 &&
         elements[parent(currentIndex)] < elements[currentIndex]) {
    std::swap(elements[currentIndex], elements[parent(currentIndex)]);
    currentIndex = parent(currentIndex);
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
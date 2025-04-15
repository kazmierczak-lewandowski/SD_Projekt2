#ifndef HEAP_HPP
#define HEAP_HPP
#include "Collection.hpp"
#include "Element.hpp"

#include <memory>
#include <span>
#include <vector>

class Heap final : public Collection {
public:
  explicit Heap() : elements(std::make_unique<Element[]>(10)), capacity(10) {};
  Heap(const std::span<Element> elements, const int capacity)
      : elements(std::make_unique<Element[]>(std::size(elements))),
        capacity(capacity) {
    setSize(static_cast<int>(std::size(elements)));
    for (int i = 0; i < getSize(); ++i) {
      this->elements[i] = elements[i];
    }
    for (int i = getSize() / 2 - 1; i >= 0; --i) {
      heapifyDown(i);
    }
  }
  [[nodiscard]] int getCapacity() const { return capacity; }
  [[nodiscard]] Element *getElements() const { return elements.get(); }
  explicit Heap(const std::span<Element> elements)
      : Heap(elements, static_cast<int>(std::size(elements))) {};
  ~Heap() override = default;
  [[nodiscard]] std::vector<std::vector<Element>> getLevels() const override;
  void insert(Element element) override;
  Element extractMax() override;
  [[nodiscard]] Element peek() const override;
  [[nodiscard]] int findElement(const Element &element,
                                int index) const override;
  void modifyKey(Element element, int newPriority) override;
  [[nodiscard]] int getHeight() const override;

private:
  std::unique_ptr<Element[]> elements;
  int capacity{};
  void heapifyDown(int index);
  void heapifyUp(int index);
  [[nodiscard]] static int left(int index);
  [[nodiscard]] static int right(int index);
  [[nodiscard]] static int parent(int index);
  void ensureCapacity();
  void grow();
};

#endif // HEAP_HPP

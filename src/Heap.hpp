#ifndef HEAP_HPP
#define HEAP_HPP
#include "Collection.hpp"
#include "Element.hpp"

#include <memory>
#include <vector>
class Heap final : public Collection {
public:
  explicit Heap();
  explicit Heap(const std::span<Element> arr) : Heap(arr, static_cast<int>(arr.size())) {};
  explicit Heap(std::span<Element> arr, int capacity);
  ~Heap() override = default;
  [[nodiscard]] std::vector<std::vector<Element>> getLevels() const override;
  void insert(Element element, int priority) override;
  Element extractMax() override;
  [[nodiscard]] Element peek() const override;
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

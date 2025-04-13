#ifndef HEAP_HPP
#define HEAP_HPP
#include "Collection.hpp"

#include <memory>

class Heap final : public Collection {
public:
  explicit Heap();
  explicit Heap(std::span<int> arr);
  explicit Heap(std::span<int> arr, int capacity);
  ~Heap() override = default;
  void insert(int value, int priority) override;
  int extractMax() override;
  int peek() override;
  void modifyKey(int value, int newPriority) override;
  void getHeight() override;

private:
  std::unique_ptr<int[]> elements;
  int capacity{};
  void heapify(int index);
  [[nodiscard]] static int left(int index);
  [[nodiscard]] static int right(int index);
  [[nodiscard]] static int parent(int index);
  void ensureCapacity();
  void grow();
};

#endif // HEAP_HPP

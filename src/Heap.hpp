#ifndef HEAP_HPP
#define HEAP_HPP
#include "Collection.hpp"

#include <memory>
#include <vector>
class Heap final : public Collection {
public:
  explicit Heap();
  explicit Heap(const std::span<int> arr) : Heap(arr, static_cast<int>(arr.size())) {};
  explicit Heap(std::span<int> arr, int capacity);
  ~Heap() override = default;
  [[nodiscard]] std::vector<std::vector<int>> getLevels() const override;
  void insert(int value, int priority) override;
  int extractMax() override;
  [[nodiscard]] int peek() const override;
  void modifyKey(int value, int newPriority) override;
  [[nodiscard]] int getHeight() const override;
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

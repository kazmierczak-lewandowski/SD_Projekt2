#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include <vector>

class Collection {
public:
  virtual ~Collection() = default;
  [[nodiscard]] virtual std::vector<std::vector<int>> getLevels() const = 0;
  virtual void insert(int value, int priority) = 0;
  virtual int extractMax() = 0;
  [[nodiscard]] virtual int peek() const = 0;
  virtual void modifyKey(int value, int newPriority) = 0;
  [[nodiscard]] virtual int getHeight() const = 0;
  [[nodiscard]] int getSize() const { return size; }

protected:
  void setSize(const int newSize) { size = newSize; }

private:
  int size = 0;
};

#endif // COLLECTION_HPP

#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include "Element.hpp"

#include <vector>

class Collection {
public:
  virtual ~Collection() = default;
  [[nodiscard]] virtual std::vector<std::vector<Element>> getLevels() const = 0;
  virtual void insert(Element element, int priority) = 0;
  virtual Element extractMax() = 0;
  [[nodiscard]] virtual Element peek() const = 0;
  [[nodiscard]] virtual int findElement(const Element &element, int index) const = 0;
  virtual void modifyKey(Element element, int newPriority) = 0;
  [[nodiscard]] virtual int getHeight() const = 0;
  [[nodiscard]] int getSize() const { return size; }

protected:
  void setSize(const int newSize) { size = newSize; }

private:
  int size = 0;
};

#endif // COLLECTION_HPP

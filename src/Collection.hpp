#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include "Element.hpp"
#include "Utils.hpp"

#include <bits/ranges_algo.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <vector>

class Collection {
public:
  virtual ~Collection() = default;
  [[nodiscard]] virtual std::vector<std::vector<Element>> getLevels() const = 0;
  virtual void insert(Element element) = 0;
  virtual Element extractMax() = 0;
  [[nodiscard]] virtual Element peek() const = 0;
  [[nodiscard]] virtual int findElement(const Element &element,
                                        int index) const = 0;
  virtual void modifyKey(const Element &element, int newPriority) = 0;
  virtual void print() const;
  [[nodiscard]] virtual int getHeight() const {
    return !isEmpty() ? static_cast<int>(std::log2(getSize())) : 0;
  }
  [[nodiscard]] int getSize() const { return size; }
  static void fillWithRandom(Collection &collection, const int size);
  static void fillFromFile(Collection &collection, const std::string &filename);
  Element getRandomElement() const;
  [[nodiscard]] bool isEmpty() const { return size == 0; }

protected:
  void setSize(const int newSize) { size = newSize; }

private:
  int size = 0;
};

#endif // COLLECTION_HPP

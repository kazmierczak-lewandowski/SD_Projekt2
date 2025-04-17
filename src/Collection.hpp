#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include "Element.hpp"

#include <bits/ranges_algo.h>
#include <cmath>
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
  virtual void print() const {
    const auto levels = getLevels();
    std::vector<size_t> spaces;
    for (int i = static_cast<int>(levels.size()) - 1; i >= 0; i--) {
      std::string levelString;
      auto prevSpaces = spaces;
      spaces.clear();
      for (int j = 0; j < levels[i].size(); j++) {
        auto element = levels[i][j];
        auto elementString = element.toString();
        int numOfSpaces = 0;
        if (!prevSpaces.empty()) {
          numOfSpaces =
              static_cast<int>(prevSpaces[j] - elementString.find(';') - levelString.size());
          levelString += std::string(numOfSpaces, ' ');
        }
        if (j % 2 == 1) {
          spaces.push_back(levelString.size() - static_cast<int>(std::ceil(numOfSpaces/2.0))); //Not right forumula
        }
        levelString += std::format("{} ", element.toString());

      }
      mvprintw(i, 0, "%s", levelString.c_str());
    }
  };
  [[nodiscard]] virtual int getHeight() const {
    return getSize() != 0 ? static_cast<int>(std::log2(getSize())) : 0;
  };
  [[nodiscard]] int getSize() const { return size; }

protected:
  void setSize(const int newSize) { size = newSize; }

private:
  int size = 0;
};

#endif // COLLECTION_HPP

#ifndef ELEMENT_HPP
#define ELEMENT_HPP
#include <compare>

class Element {
public:
  Element(const int value, const int priority)
      : value(value), priority(priority) {}
  auto operator<=>(const Element &other) const {
    return priority <=> other.priority;
  };
  bool operator==(const Element &other) const {
    return priority == other.priority;
  }
  [[nodiscard]] int getValue() const { return value; }
  [[nodiscard]] int getPriority() const { return priority; }
  [[nodiscard]] bool checkValue(const Element &other) const {
    return value == other.value;
  }
  [[nodiscard]] bool checkValue(const int otherValue) const {
    return value == otherValue;
  }
private:
  const int value;
  int priority;
};

#endif // ELEMENT_HPP

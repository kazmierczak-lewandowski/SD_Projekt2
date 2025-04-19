#ifndef ELEMENT_HPP
#define ELEMENT_HPP
#include <compare>
#include <ostream>

class Element {
public:
  Element(const int value, const int priority)
      : value(value), priority(priority) {}
  Element() : value(-1), priority(-1) {}
  auto operator<=>(const Element &other) const {
    return priority <=> other.priority;
  };
  bool operator==(const Element &other) const {
    return (priority == other.priority) && (value == other.value);
  }
  void setPriority(const int newPriority) { this->priority = newPriority; }
  [[nodiscard]] int getValue() const { return value; }
  [[nodiscard]] int getPriority() const { return priority; }
  [[nodiscard]] bool checkValue(const Element &other) const {
    return value == other.value;
  }
  [[nodiscard]] bool checkValue(const int otherValue) const {
    return value == otherValue;
  }
  [[nodiscard]] std::string toString() const {
    return std::format("({};{})", priority, value);
  }

private:
  int value;
  int priority;
};

#endif // ELEMENT_HPP

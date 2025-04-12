#ifndef NODE_HPP
#define NODE_HPP
#include <compare>

class Node {
private:
  int value;
  int priority;
  public:
  Node(const int value, const int priority) : value(value), priority(priority) {};
  [[nodiscard]] int getValue() const { return value; }
  [[nodiscard]] int getPriority() const { return priority; }
  auto operator<=>(const Node& other) const {
    return priority <=> other.priority;
  }
  bool operator==(const Node& other) const {
    return priority == other.priority;
  }
};



#endif //NODE_HPP

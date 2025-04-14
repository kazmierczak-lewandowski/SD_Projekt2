#include "Element.hpp"
Element &Element::operator=(const Element &other) {
  if (this != &other) {
    value = other.value;
    priority = other.priority;
  }
  return *this;
}
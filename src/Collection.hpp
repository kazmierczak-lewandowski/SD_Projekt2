#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include "Node.hpp"

class Collection {
public:
  virtual ~Collection() = default;
  virtual void insert(int value, int priority) = 0;
  virtual Node extractMax() = 0;
  virtual Node peek() = 0;
  virtual void modifyKey(int value, int newPriority) = 0;
  virtual void getSize() = 0;
};



#endif //COLLECTION_HPP

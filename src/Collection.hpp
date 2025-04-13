#ifndef COLLECTION_HPP
#define COLLECTION_HPP

class Collection {
public:
  virtual ~Collection() = default;
  virtual void insert(int value, int priority) = 0;
  virtual int extractMax() = 0;
  virtual int peek() = 0;
  virtual void modifyKey(int value, int newPriority) = 0;
  virtual void getHeight() = 0;

protected:
  void SetSize(const int newSize) { size = newSize; }
  [[nodiscard]] int getSize() const { return size; }

private:
  int size = 0;
};

#endif // COLLECTION_HPP

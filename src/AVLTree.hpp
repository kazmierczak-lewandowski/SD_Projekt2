#ifndef AVLTree_HPP
#define AVLTree_HPP
#include <memory>

#include "Collection.hpp"

class AVLTree final : public Collection{
private:
  struct AVLNode{
    Element element;
    std::unique_ptr<AVLNode> left = nullptr;
    std::unique_ptr<AVLNode> right = nullptr;
    AVLNode *parent = nullptr;
    int height = 0;
    explicit AVLNode(Element const e) : element(e){}
  };
  std::unique_ptr<AVLNode> root = nullptr;
public:
  explicit AVLTree() = default;
  ~AVLTree() override = default;
  [[nodiscard]] std::vector<std::vector<Element>> getLevels() const override;
  void insert(Element element) override;
  Element extractMax() override;
  [[nodiscard]] Element peek() const override;
  [[nodiscard]] int findElement(const Element& element, int index) const override;
  void modifyKey(const Element& element, int newPriority) override;
};

#endif // AVLTree_HPP

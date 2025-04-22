#ifndef AVLTree_HPP
#define AVLTree_HPP
#include <memory>

#include "Collection.hpp"

class AVLTree final : public Collection {

public:
  struct AVLNode{
    Element element;
    std::unique_ptr<AVLNode> left = nullptr;
    std::unique_ptr<AVLNode> right = nullptr;
    AVLNode *parent = nullptr;
    int height = 0;
    explicit AVLNode(Element const e) : element(e){}
  };
  explicit AVLTree() = default;
  ~AVLTree() override = default;
  [[nodiscard]] std::vector<std::vector<Element>> getLevels() const override;
  void insert(Element element) override;
  Element extractMax() override;
  [[nodiscard]] Element peek() const override;
  [[nodiscard]] AVLNode* findElement(const Element &element) const;
  void modifyKey(const Element& element, int newPriority) override;
  [[nodiscard]] AVLNode* getRoot() const {
    return root.get();
  }
private:
  std::unique_ptr<AVLNode> root = nullptr;
  void LLRotation(AVLNode *current);
  void RRRotation(AVLNode *current);
  void LRRotation(AVLNode *current);
  void RLRotation(AVLNode *current);
  static int checkBalance(const AVLNode *current);
  void balance(AVLNode *current);
  static void updateHeight(AVLNode *node);
  void updateBalanceUp(AVLNode *node);
  static void getLevels(const AVLNode *current, std::vector<std::vector<Element>> &elements);
};

#endif // AVLTree_HPP

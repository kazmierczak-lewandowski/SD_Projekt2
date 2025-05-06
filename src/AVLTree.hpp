#ifndef AVLTree_HPP
#define AVLTree_HPP
#include <memory>

#include "Collection.hpp"

#include <queue>

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
  static void getLevelsInsider(std::queue<const AVLNode *> &q, int levelSize,
                               std::vector<Element> currentLevel,
                               bool &hasValidNode);
  [[nodiscard]] Element peek() const override;
  [[nodiscard]] AVLNode* findElement(const Element &element) const;
  void modifyKey(const Element& element, int newPriority) override;
  [[nodiscard]] AVLNode* getRoot() const {
    return root.get();
  }
  void deleteNodeByElement(const Element &element);
private:
  std::unique_ptr<AVLNode> root = nullptr;
  void LLRotation(std::unique_ptr<AVLNode> &current);
  void RRRotation(std::unique_ptr<AVLNode> &current);
  void LRRotation(std::unique_ptr<AVLNode> &current);
  void RLRotation(std::unique_ptr<AVLNode> &current);
  static int checkBalance(const AVLNode *current);
  void balance(std::unique_ptr<AVLNode> &current);
  static void updateHeight(AVLNode *node);
  void updateBalanceUp(AVLNode *node);
  static void getLevels(const AVLNode *current, std::vector<std::vector<Element>> &elements);
  void deleteNode(AVLNode *node);
  Element extractMaxFromSubtree(AVLNode *node);
};

#endif // AVLTree_HPP

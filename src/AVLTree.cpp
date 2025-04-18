#include "AVLTree.hpp"
void AVLTree::insert(Element element) {
  auto newNode = std::make_unique<AVLNode>(element);
  if (getSize() == 0) {
    root = std::move(newNode);
    setSize(getSize()+1);
    return;
  }
  auto current = root.get();
  AVLNode* parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (newNode->element < current->element) {
      current = current->left.get();
      continue;
    }
    current = current->right.get();
  }
  newNode->parent = parent;
  if (parent != nullptr) {
    if (newNode->element < parent->element) {
      parent->left = std::move(newNode);
    } else {
      parent->right = std::move(newNode);
    }
  }
  setSize(getSize()+1);
  current = parent;
  while (current != nullptr) {
    updateHeight(current);
    if (std::abs(checkBalance(current)) > 1) {
      balance(current);
    }
    current = current->parent;
  }
}
void AVLTree::modifyKey(const Element& element, int newPriority){

}
Element AVLTree::peek() const {

}
Element AVLTree::extractMax() {

}
std::vector<std::vector<Element>> AVLTree::getLevels() const {

}
int AVLTree::findElement(const Element& element, int index) const {

}
void AVLTree::RRRotation(AVLNode* current) {
  std::unique_ptr<AVLNode> temp = std::move(current->right);
  current->right = std::move(temp->left);
  temp->left = std::move(current->parent->right);
  current->parent->right = std::move(temp);
  updateHeight(current);
}
void AVLTree::LLRotation(AVLNode* current) {
  std::unique_ptr<AVLNode> temp = std::move(current->left);
  current->left = std::move(temp->right);
  temp->right = std::move(current->parent->left);
  current->parent->left = std::move(temp);
  updateHeight(current);
}
void AVLTree::LRRotation(AVLNode* current) {
  RRRotation(current->left.get());
  LLRotation(current);
}
void AVLTree::RLRotation(AVLNode* current) {
  LLRotation(current->right.get());
  RRRotation(current);
}
int AVLTree::checkBalance(AVLNode* current) {
  int leftHeight = current->left ? current->left->height : -1;
  int rightHeight = current->right ? current->right->height : -1;
  return leftHeight - rightHeight;
}
void AVLTree::balance(AVLNode* node) {
  if (!node) return;

  updateHeight(node);

  int balance_factor = checkBalance(node);

  if (balance_factor > 1) {
    if (checkBalance(node->left.get()) >= 0) {
      LLRotation(node);
    } else {
      LRRotation(node);
    }
  }
  else if (balance_factor < -1) {
    if (checkBalance(node->right.get()) <= 0) {
      RRRotation(node);
    } else {
      RLRotation(node);
    }
  }
}

void AVLTree::updateHeight(AVLNode* node) {
  int leftHeight = node->left ? node->left->height : -1;
  int rightHeight = node->right ? node->right->height : -1;
  node->height = 1 + std::max(leftHeight, rightHeight);
}
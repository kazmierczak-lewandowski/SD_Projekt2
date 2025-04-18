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
    if (std::abs(checkBalance(current)) > 1) {
      balance(current);
    }
    updateHeight(current);
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
void AVLTree::LLRotation(AVLNode* current) {
  std::unique_ptr<AVLNode> temp = std::move(current->right);
  current->right = std::move(temp->left);
  temp->left = std::move(current->parent->right);
  current->parent->right = std::move(temp);
}
void AVLTree::RRRotation(AVLNode* current) {
  std::unique_ptr<AVLNode> temp = std::move(current->left);
  current->left = std::move(temp->right);
  temp->right = std::move(current->parent->left);
  current->parent->left = std::move(temp);
}
void AVLTree::LRRotation(AVLNode* current) {
  LLRotation(current);
  RRRotation(current);
}
void AVLTree::RLRotation(AVLNode* current) {
  RRRotation(current);
  LLRotation(current);
}
int AVLTree::checkBalance(AVLNode* current) {
  if (current->left == nullptr && current->right == nullptr) return 0;
  if (current->left == nullptr) return -1 - current->right->height;
  if (current->right == nullptr) return current->left->height +1;
  return current->left->height - current->right->height;
}
void AVLTree::balance(AVLNode* current) {
  if (checkBalance(current)>1 && checkBalance(current->left.get())>1) RRRotation(current);
  else if (checkBalance(current)>1 && checkBalance(current->left.get())<1) LRRotation(current);
  else if (checkBalance(current)<1 && checkBalance(current->left.get())>1) LLRotation(current);
  else if (checkBalance(current)<1 && checkBalance(current->left.get())<1) RLRotation(current);
}

void AVLTree::updateHeight(AVLNode* node) {
  int leftHeight = node->left ? node->left->height : 0;
  int rightHeight = node->right ? node->right->height : 0;
  node->height = 1 + std::max(leftHeight, rightHeight);
}
#include "AVLTree.hpp"
void AVLTree::insert(Element element) {
  auto newNode = std::make_unique<AVLNode>(element);
  if (getSize() == 0) {
    root = std::move(newNode);
    setSize(getSize()+1);
    return;
  }
  auto current = root.get();
  while (current!=nullptr) {
    if (newNode->element < current->element) {
      current = current->left.get();
      continue;
    }
    current = current->right.get();
  }
  newNode.reset(current);
  current = newNode.get();
  setSize(getSize()+1);
  while (current!=nullptr) {
    balance(current);
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

}
void AVLTree::RRRotation(AVLNode* current) {
  std::unique_ptr<AVLNode> temp = std::move(current->left);
  current->left = std::move(temp->right);
  temp->right = std::move(current->parent->left);
  current->parent->left = std::move(temp);
}
void AVLTree::LRRotation(AVLNode* current) {

}
void AVLTree::RLRotation(AVLNode* current) {

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


#include "AVLTree.hpp"
void AVLTree::insert(Element element) {
  auto newNode = std::make_unique<AVLNode>(element);
  if (getSize() == 0) {
    root = std::move(newNode);
    return;
  }
  auto current = root.get();
  for (int i = getHeight(); i>=0; i++) { //for or while?
    if (newNode->element < current->element) {
      current = current->left.get();
    } else {
      current = current->right.get();
    }
  }
  newNode.reset(current);
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



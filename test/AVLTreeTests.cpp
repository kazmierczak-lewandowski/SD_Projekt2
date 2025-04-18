#include "../src/AVLTree.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <cmath>
void printTree(const AVLTree::AVLNode* node, const std::string& prefix = "", bool isLeft = true) {
  if (node == nullptr) return;

  std::cout << prefix;

  std::cout << (isLeft ? "├──" : "└──");

  std::cout << "(" << node->element.getValue() << ", " << node->element.getPriority() << ", h=" << node->height << ")" << std::endl;

  printTree(node->left.get(), prefix + (isLeft ? "│   " : "    "), true);
  printTree(node->right.get(), prefix + (isLeft ? "│   " : "    "), false);
}

bool isCorrect(AVLTree::AVLNode *node) {
  if (node == nullptr) return true;
  if (node->left && node->left->element > node->element) return false;
  if (node->right && node->right->element < node->element) return false;
  return isCorrect(node->left.get()) && isCorrect(node->right.get());
}

bool isBalanced(AVLTree::AVLNode *node) {
  if (node == nullptr) return true;

  int leftHeight = node->left ? node->left->height : -1;
  int rightHeight = node->right ? node->right->height : -1;

  if (std::abs(leftHeight - rightHeight) > 1) return false;

  return isBalanced(node->left.get()) && isBalanced(node->right.get());
}
void add7ElementsForTests(AVLTree &avl) {
  avl.insert(Element{1, 10});
  avl.insert(Element{2, 11});
  avl.insert(Element{3, 8});
  avl.insert(Element{2, 12});
  avl.insert(Element{1, 9});
  avl.insert(Element{2, 7});
  avl.insert(Element{3, 6});
  avl.insert(Element{2, 5});
  avl.insert(Element{2, 4});
  avl.insert(Element{2, 3});
  avl.insert(Element{2, 17});
  //avl.insert(Element{2, 18});
  avl.insert(Element{3, 16});
  avl.insert(Element{2, 15});
  // avl.insert(Element{2, 13});
  // avl.insert(Element{2, 14});
}
TEST(AVLTreeTests, insert) {
  AVLTree avl;
  add7ElementsForTests(avl);
  printTree(avl.getRoot());
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
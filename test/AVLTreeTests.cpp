#include "../src/AVLTree.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <cmath>

bool isCorrect(const AVLTree::AVLNode *node) { // NOLINT(*-no-recursion)
  if (node == nullptr) return true;
  if (node->left) {
    if (node->left->element > node->element || node->left->parent != node) return false;
  }
  if (node->right) {
    if (node->right->element < node->element || node->right->parent != node) return false;
  }
  return isCorrect(node->left.get()) && isCorrect(node->right.get());
}

bool isBalanced(const AVLTree::AVLNode *node) { // NOLINT(*-no-recursion)
  if (node == nullptr) return true;

  const int leftHeight = node->left ? node->left->height : -1;
  const int rightHeight = node->right ? node->right->height : -1;

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
  avl.insert(Element{2, 18});
  avl.insert(Element{3, 16});
  avl.insert(Element{2, 15});
  avl.insert(Element{2, 13});
  avl.insert(Element{2, 14});
  avl.insert(Element{2, 2});
  avl.insert(Element{2, 1});
  avl.insert(Element{2, 0});
}
TEST(AVLTreeTests, insert) {
  AVLTree avl;
  add7ElementsForTests(avl);
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
  EXPECT_EQ(avl.getSize(), 19);
}
TEST(AVLTreeTests, RRRotationParentRight) {
  AVLTree avl;
  avl.insert(Element{1, 5});
  avl.insert(Element{2, 6});
  avl.insert(Element{3, 4});
  avl.insert(Element{4, 7});
  avl.insert(Element{5, 8});
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, RRRotationParentLeft) {
  AVLTree avl;
  avl.insert(Element{1, 10});
  avl.insert(Element{2, 6});
  avl.insert(Element{3, 11});
  avl.insert(Element{4, 7});
  avl.insert(Element{5, 8});
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}

TEST(AVLTreeTests, RRRotationWithRoot) {
  AVLTree avl;
  avl.insert(Element{1, 1});
  avl.insert(Element{2, 2});
  avl.insert(Element{3, 3});
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, LLRotationWithRoot) {
  AVLTree avl;
  avl.insert(Element{1, 3});
  avl.insert(Element{2, 2});
  avl.insert(Element{3, 1});
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, LLRotationParentLeft) {
  AVLTree avl;
  avl.insert(Element{1, 10});
  avl.insert(Element{2, 6});
  avl.insert(Element{3, 11});
  avl.insert(Element{4, 5});
  avl.insert(Element{5, 4});
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, LLRotationParentRight) {
  AVLTree avl;
  avl.insert(Element{1, 10});
  avl.insert(Element{2, 12});
  avl.insert(Element{3, 8});
  avl.insert(Element{4, 7});
  avl.insert(Element{5, 6});
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
// TEST(AVLTreeTests, getLevels) {
//   AVLTree avl;
//   avl.insert(Element{1, 10});
//   avl.insert(Element{1, 8});
//   avl.insert(Element{1, 11});
//   avl.insert(Element{1, 5});
//   avl.insert(Element{1, 9});
//   avl.insert(Element{1, 12});
//   avl.insert(Element{1, 6});
//
//   const auto levels = avl.getLevels();
//
//   const std::vector<std::vector<Element>> expectedLevels = {
//     {{1,10}},
//     {{1,8}, {1,11}},
//     {{1,5}, {1,9}, {-1,-1}, {1,12}},
//     {{-1,-1}, {1,6}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}}
//   };
//
//   ASSERT_EQ(levels.size(), expectedLevels.size());
//   for (size_t i = 0; i < levels.size(); ++i) {
//     ASSERT_EQ(levels[i].size(), expectedLevels[i].size());
//     for (size_t j = 0; j < levels[i].size(); ++j) {
//       EXPECT_EQ(levels[i][j], expectedLevels[i][j]);
//     }
//   }
// }

TEST(AVLTreeTests, extractMax) {
  AVLTree avl;
  avl.insert(Element{1, 3});
  avl.insert(Element{1, 2});
  avl.insert(Element{1, 1});
  avl.insert(Element{1, 1});
  avl.insert(Element{1, 1});
  avl.insert(Element{1, 4});
  avl.insert(Element{1, 5});
  avl.insert(Element{1, 6});
  avl.insert(Element{1, 7});
  avl.insert(Element{1, 8});
  avl.insert(Element{1, 4});
  avl.insert(Element{1, 5});
  avl.insert(Element{1, 6});
  avl.extractMax();
  avl.extractMax();
  avl.extractMax();
  avl.extractMax();
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, deleting) {
  AVLTree avl;
  avl.insert(Element{1, 10});
  avl.insert(Element{1, 8});
  avl.insert(Element{1, 12});
  avl.insert(Element{1, 9});
  avl.insert(Element{1, 7});
  avl.insert(Element{1, 6});
  avl.deleteNodeByElement(Element(1,12));
  avl.deleteNodeByElement(Element(1,9));
  avl.deleteNodeByElement(Element(1,10));
  EXPECT_EQ(avl.getSize(), 3);
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, modifyKey) {
  AVLTree avl;
  avl.insert(Element{1, 10});
  avl.insert(Element{1, 8});
  avl.insert(Element{1, 12});
  avl.insert(Element{1, 9});
  avl.insert(Element{1, 7});
  avl.modifyKey(Element(1,10),13);
  //avl.modifyKey(Element(1,10),13);
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, randomTree) {
  AVLTree avl;
  for (int i = 0; i < 100'000; ++i) {
    const int key = Utils::rng(0, 1'000'000);
    const int value = Utils::rng(0, 1'000'000);
    avl.insert(Element{key, value});
  }
  ASSERT_EQ(avl.getSize(), 100'000);
  ASSERT_TRUE(isCorrect(avl.getRoot()));
  ASSERT_TRUE(isBalanced(avl.getRoot()));
  const auto element = avl.getRandomElement();
  const auto foundElement = avl.findElement(element);
  ASSERT_TRUE(foundElement != nullptr);
  EXPECT_NE(foundElement->element, Element(-1, -1));
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
TEST(AVLTreeTests, treeFromFile) {
  AVLTree avl;
  AVLTree::fillFromFile(avl, "/home/piotr/CLionProjects/SD_Projekt2/numbers.txt",
                   100'000);
  ASSERT_EQ(avl.getSize(), 100'000);
  ASSERT_TRUE(isCorrect(avl.getRoot()));
  ASSERT_TRUE(isBalanced(avl.getRoot()));
  const auto element = avl.getRandomElement();
  const auto foundElement = avl.findElement(element);
  ASSERT_TRUE(foundElement != nullptr);
  EXPECT_NE(foundElement->element, Element(-1, -1));
  EXPECT_TRUE(isCorrect(avl.getRoot()));
  EXPECT_TRUE(isBalanced(avl.getRoot()));
}
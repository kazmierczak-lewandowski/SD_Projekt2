#include <gtest/gtest.h>
#include "../src/Node.hpp"

TEST(NodeTests, ConstructorAndGetters) {
  const Node node(10, 5);
  EXPECT_EQ(node.getValue(), 10);
  EXPECT_EQ(node.getPriority(), 5);
}

TEST(NodeTests, ComparisonEquality) {
  const Node node1(1, 2);
  const Node node2(3, 2);
  EXPECT_EQ(node1, node2);
}

// Test comparison operator (greater than)
TEST(NodeTests, ComparisonGreaterThan) {
  const Node node1(1, 3);
  const Node node2(2, 2);
  EXPECT_GT(node1, node2);
}

// Test comparison operator (less than)
TEST(NodeTests, ComparisonLessThan) {
  const Node node1(1, 1);
  const Node node2(2, 2);
  EXPECT_LT(node1, node2);
}
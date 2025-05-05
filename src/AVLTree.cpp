#include "AVLTree.hpp"

#include <iostream>

void AVLTree::insert(Element element) {
  auto newNode = std::make_unique<AVLNode>(element);
  if (getSize() == 0) {
    root = std::move(newNode);
    setSize(getSize() + 1);
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
  setSize(getSize() + 1);
  updateBalanceUp(parent);
}
void AVLTree::modifyKey(const Element& element, const int newPriority) {
  auto node = findElement(element);
  const int value = node->element.getValue();
  deleteNode(node);
  insert(Element(value, newPriority));
}

Element AVLTree::peek() const {
  auto current = root.get();
  while (current->right != nullptr) {
    current = current->right.get();
  }
  return current->element;
}
Element AVLTree::extractMaxFromSubtree(AVLNode* current) {
  while (current->right != nullptr) {
    current = current->right.get();
  }
  if (current == root.get()) {
    root = std::move(current->left);
    updateBalanceUp(root.get());
    return current->element;
  }
  auto parent = current->parent;
  const Element currentElement = current->element;
  if (current->left) current->left->parent = current->parent;
  current->parent->right = std::move(current->left);
  if (parent != nullptr) updateBalanceUp(parent);
  return currentElement;
}

Element AVLTree::extractMax() {
  auto current = root.get();
  return extractMaxFromSubtree(current);
}

std::vector<std::vector<Element>> AVLTree::getLevels() const {
  if (root == nullptr) return {};
  std::vector<std::vector<Element>> elements;
  elements.emplace_back();
  elements[0].push_back(root->element);
  getLevels(root.get(), elements);
  elements.pop_back();
  for (int i = 0; i < elements[elements.size() - 2].size(); i++) {
    if (elements[elements.size() - 2][i] == Element(-1, -1)) {
      elements[elements.size() - 1].insert(
          elements[elements.size() - 1].begin() + 2 * i, Element(-1, -1));
      elements[elements.size() - 1].insert(
          elements[elements.size() - 1].begin() + 2 * i + 1, Element(-1, -1));
    }
  }
  return elements;
}
void AVLTree::getLevels(const AVLNode* current, // NOLINT(*-no-recursion)
                        std::vector<std::vector<Element>>& elements) {
  if (current == nullptr) return;
  int height = 0;
  auto temp = current->parent;
  while (temp != nullptr) {
    height++;
    temp = temp->parent;
  }
  if (elements.size() <= height + 1) {
    elements.emplace_back();
  }
  if (current->left == nullptr) {
    elements[height + 1].emplace_back(-1, -1);
  } else {
    elements[height + 1].push_back(current->left->element);
  }
  if (current->right == nullptr) {
    elements[height + 1].emplace_back(-1, -1);
  } else {
    elements[height + 1].push_back(current->right->element);
  }
  getLevels(current->left.get(), elements);
  getLevels(current->right.get(), elements);
}

void AVLTree::deleteNode(AVLNode* node) { // NOLINT(*-no-recursion)
  if (node == nullptr) return;

  AVLNode* parent = nullptr;

  if (node->left == nullptr && node->right == nullptr) {
    parent = node->parent;
    if (node == root.get()) {
      root.reset();
    } else {
      if (parent->left.get() == node) {
        parent->left.reset();
      } else {
        parent->right.reset();
      }
    }
  }

  else if (node->left == nullptr || node->right == nullptr) {
    parent = node->parent;
    std::unique_ptr<AVLNode>& child =
        node->left != nullptr ? node->left : node->right;
    if (node == root.get()) {
      root = std::move(child);
      root->parent = nullptr;
    } else {
      if (node->parent->left.get() == node) {
        child->parent = node->parent;
        parent->left = std::move(child);
      } else {
        child->parent = node->parent;
        parent->right = std::move(child);
      }
    }
  }

  else {
    AVLNode* successor = node->right.get();
    while (successor->left) {
      successor = successor->left.get();
    }
    node->element = successor->element;
    deleteNode(successor);
    return;
  }
  updateBalanceUp(parent);
}

void AVLTree::deleteNodeByElement(const Element& element) {
  const auto node = findElement(element);
  deleteNode(node);
}

AVLTree::AVLNode* AVLTree::findElement(const Element& element) const {
  AVLNode* current = root.get();
  while (current->element != element) {
    if (element < current->element) {
      current = current->left.get();
      continue;
    }
    current = current->right.get();
  }
  return current;
}
void AVLTree::RRRotation(AVLNode* current) {
  std::unique_ptr<AVLNode> currentRight = std::move(current->right);
  current->right = std::move(currentRight->left);
  if (current->right) current->right->parent = current;
  currentRight->parent = current->parent;
  if (current->parent) {
    if (current->parent->right.get() == current) {
      currentRight->left = std::move(current->parent->right);
      current->parent->right = std::move(currentRight);
    } else {
      currentRight->left = std::move(current->parent->left);
      current->parent->left = std::move(currentRight);
    }
  } else {
    currentRight->left = std::move(root);
    root = std::move(currentRight);
  }
  updateHeight(current);
}
void AVLTree::LLRotation(AVLNode* current) {
  std::unique_ptr<AVLNode> currentLeft = std::move(current->left);
  current->left = std::move(currentLeft->right);
  if (current->left) current->left->parent = current;
  currentLeft->parent = current->parent;
  if (current->parent) {
    if (current->parent->left.get() == current) {
      currentLeft->right = std::move(current->parent->left);
      current->parent->left = std::move(currentLeft);
    } else {
      currentLeft->right = std::move(current->parent->right);
      current->parent->right = std::move(currentLeft);
    }
  } else {
    currentLeft->right = std::move(root);
    root = std::move(currentLeft);
  }
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
int AVLTree::checkBalance(const AVLNode* current) {
  const int leftHeight = current->left ? current->left->height : -1;
  const int rightHeight = current->right ? current->right->height : -1;
  return leftHeight - rightHeight;
}
void AVLTree::balance(AVLNode* node) {
  if (!node) return;

  updateHeight(node);

  const int balance_factor = checkBalance(node);

  if (balance_factor > 1) {
    if (checkBalance(node->left.get()) >= 0) {
      LLRotation(node);
    } else {
      LRRotation(node);
    }
  } else if (balance_factor < -1) {
    if (checkBalance(node->right.get()) <= 0) {
      RRRotation(node);
    } else {
      RLRotation(node);
    }
  }
}

void AVLTree::updateHeight(AVLNode* node) {
  const int leftHeight = node->left ? node->left->height : -1;
  const int rightHeight = node->right ? node->right->height : -1;
  node->height = 1 + std::max(leftHeight, rightHeight);
}
void AVLTree::updateBalanceUp(AVLNode* current) {
  while (current != nullptr) {
    updateHeight(current);
    if (std::abs(checkBalance(current)) > 1) {
      balance(current);
    }
    current = current->parent;
  }
}

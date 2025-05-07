#include "AVLTree.hpp"

#include <algorithm>
#include <queue>

void AVLTree::insert(Element element) {
  auto newNode = std::make_unique<AVLNode>(element);
  if (isEmpty()) {
    root = std::move(newNode);
    setSize(getSize() + 1);
    return;
  }
  auto current = root.get();
  AVLNode *parent = nullptr;
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
void AVLTree::modifyKey(const Element &element, const int newPriority) {
  const auto node = findElement(element);
  if (node == nullptr) {
    return;
  }
  const int value = node->element.getValue();
  auto newElement = Element(value, newPriority);
  deleteNode(node);
  insert(newElement);
}

Element AVLTree::peek() const {
  auto current = root.get();
  while (current->right != nullptr) {
    current = current->right.get();
  }
  return current->element;
}
Element AVLTree::extractMaxFromSubtree(AVLNode *node) {
  while (node->right != nullptr) {
    node = node->right.get();
  }
  if (node == root.get()) {
    root = std::move(node->left);
    root->parent = nullptr;
    updateBalanceUp(root.get());
    return node->element;
  }
  const auto parent = node->parent;
  const Element currentElement = node->element;
  if (node->left)
    node->left->parent = node->parent;
  node->parent->right = std::move(node->left);
  if (parent != nullptr)
    updateBalanceUp(parent);
  return currentElement;
}

Element AVLTree::extractMax() {
  const auto current = root.get();
  return extractMaxFromSubtree(current);
}

void AVLTree::getLevelsInsider(std::queue<const AVLNode*>& q,
                               const int levelSize,
                               std::vector<Element>& currentLevel,
                               bool &hasValidNode) {
  for (int i = 0; i < levelSize; ++i) {
    const AVLNode *node = q.front();
    q.pop();

    if (node) {
      currentLevel.push_back(node->element);
      q.push(node->left.get());
      q.push(node->right.get());
      if (node->left || node->right)
        hasValidNode = true;
    } else {
      currentLevel.emplace_back(-1, -1);
      q.push(nullptr);
      q.push(nullptr);
    }
  }
}
std::vector<std::vector<Element>> AVLTree::getLevels() const {
  std::vector<std::vector<Element>> levels;
  if (!root)
    return levels;

  std::queue<const AVLNode *> q;
  q.push(root.get());

  while (!q.empty()) {
    const auto levelSize = static_cast<int>(q.size());
    std::vector<Element> currentLevel;
    bool hasValidNode = false;

    getLevelsInsider(q, levelSize, currentLevel, hasValidNode);

    levels.push_back(currentLevel);
    if (!hasValidNode)
      break;
  }

  while (!levels.empty() &&
         std::ranges::all_of(levels.back(), [](const Element &e) {
           return e == Element(-1, -1);
         })) {
    levels.pop_back();
  }

  return levels;
}

void AVLTree::deleteNode(AVLNode *node) {
  if (node == nullptr)
    return;

  AVLNode *parent = node->parent;

  if (node->left == nullptr && node->right == nullptr) {
    if (node == root.get()) {
      root.reset();
    } else {
      if (parent->left.get() == node)
        parent->left.reset();
      else
        parent->right.reset();
    }
    setSize(getSize() - 1);
  }

  else if (node->left == nullptr || node->right == nullptr) {
    std::unique_ptr<AVLNode> &child = (node->left) ? node->left : node->right;
    if (node == root.get()) {
      root = std::move(child);
      root->parent = nullptr;
    } else {
      child->parent = parent;
      if (parent->left.get() == node)
        parent->left = std::move(child);
      else
        parent->right = std::move(child);
    }
    setSize(getSize() - 1);
  }

  else {
    AVLNode *successor = node->right.get();
    while (successor->left)
      successor = successor->left.get();
    node->element = successor->element;
    deleteNode(successor);
    return;
  }

  updateBalanceUp(parent);
}

void AVLTree::deleteNodeByElement(const Element &element) {
  const auto node = findElement(element);
  deleteNode(node);
}

AVLTree::AVLNode *AVLTree::findElement(const Element &element) const {
  AVLNode *current = root.get();
  while (current != nullptr && current->element != element) {
    if (element < current->element) {
      current = current->left.get();
      continue;
    }
    current = current->right.get();
  }
  return current;
}
void AVLTree::RRRotation(std::unique_ptr<AVLNode> &current) {
  std::unique_ptr<AVLNode> currentRight = std::move(current->right);
  const auto parent = current->parent;
  const AVLNode *parentLeft = nullptr;
  const AVLNode *parentRight = nullptr;
  if (parent != nullptr) {
    if (parent->left != nullptr){
      parentLeft = parent->left.get();
    }
    if (parent->right != nullptr){
      parentRight = parent->right.get();
    }
  }
  current->right = move(currentRight->left);
  if (current->right != nullptr) {
    current->right->parent = current.get();
  }
  currentRight->left = move(current);
  const auto original = currentRight->left.get();
  currentRight->parent = parent;
  original->parent = currentRight.get();
  updateHeight(original);
  if (parent == nullptr) {
    root = std::move(currentRight);
    updateHeight(root.get());
  } else {
    if (parentLeft == original) {
      parent->left = std::move(currentRight);
      updateHeight(parent->left.get());
    } else if (parentRight == original) {
      parent->right = std::move(currentRight);
      updateHeight(parent->right.get());
    }
  }
}
void AVLTree::LLRotation(std::unique_ptr<AVLNode> &current) {
  std::unique_ptr<AVLNode> currentLeft = std::move(current->left);
  const auto parent = current->parent;
  const AVLNode *parentLeft = nullptr;
  const AVLNode *parentRight = nullptr;
  if (parent != nullptr) {
    if (parent->left != nullptr){
      parentLeft = parent->left.get();
    }
    if (parent->right != nullptr){
      parentRight = parent->right.get();
    }
  }
  current->left = move(currentLeft->right);
  if (current->left != nullptr) {
    current->left->parent = current.get();
  }
  currentLeft->right = move(current);
  const auto original = currentLeft->right.get();
  currentLeft->parent = parent;
  original->parent = currentLeft.get();
  updateHeight(original);
  if (parent == nullptr) {
    root = std::move(currentLeft);
    updateHeight(root.get());
  } else {
    if (parentLeft == original) {
      parent->left = std::move(currentLeft);
      updateHeight(parent->left.get());
    } else if (parentRight == original) {
      parent->right = std::move(currentLeft);
      updateHeight(parent->right.get());
    }
  }
}
void AVLTree::LRRotation(std::unique_ptr<AVLNode> &current) {
  RRRotation(current->left);
  LLRotation(current);
}
void AVLTree::RLRotation(std::unique_ptr<AVLNode> &current) {
  LLRotation(current->right);
  RRRotation(current);
}
int AVLTree::checkBalance(const AVLNode *current) {
  const int leftHeight = current->left ? current->left->height : -1;
  const int rightHeight = current->right ? current->right->height : -1;
  return leftHeight - rightHeight;
}
void AVLTree::balance(std::unique_ptr<AVLNode> &current) {
  if (!current)
    return;

  updateHeight(current.get());

  if (const int balance_factor = checkBalance(current.get());
      balance_factor > 1) {
    if (checkBalance(current->left.get()) >= 0) {
      LLRotation(current);
    } else {
      LRRotation(current);
    }
  } else if (balance_factor < -1) {
    if (checkBalance(current->right.get()) <= 0) {
      RRRotation(current);
    } else {
      RLRotation(current);
    }
  }
}

void AVLTree::updateHeight(AVLNode *node) {
  const int leftHeight = node->left ? node->left->height : -1;
  const int rightHeight = node->right ? node->right->height : -1;
  node->height = 1 + std::max(leftHeight, rightHeight);
}
void AVLTree::updateBalanceUp(AVLNode *node) {
  while (node != nullptr) {
    updateHeight(node);
    if (std::abs(checkBalance(node)) > 1) {
      if (node == root.get()) {
        balance(root);
        continue;
      }
      if (node->parent->left.get() == node) {
        balance(node->parent->left);
      } else {
        balance(node->parent->right);
      }
    }
    node = node->parent;
  }
}

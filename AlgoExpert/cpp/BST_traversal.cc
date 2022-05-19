/*
Difficulty: Medium

Recursive solution is trivial.
Prefer iterative solution to prevent stack overflow for large depth tree.
TODO: in/post order iterative.
*/

#include <vector>

class BST {
 public:
  int value;
  BST *left;
  BST *right;

  BST(int val);
};

void inOrderTraverse(const BST *tree, std::vector<int> &array) {
  // Write your code here.
  if (!tree) return;
  inOrderTraverse(tree->left, array);
  array.push_back(tree->value);
  inOrderTraverse(tree->right, array);
}

void preOrderTraverse(const BST *tree, std::vector<int> &array) {
  // Write your code here.
  if (!tree) return;
  array.push_back(tree->value);
  preOrderTraverse(tree->left, array);
  preOrderTraverse(tree->right, array);
}

void postOrderTraverse(const BST *tree, std::vector<int> &array) {
  // Write your code here.
  if (!tree) return;
  postOrderTraverse(tree->left, array);
  postOrderTraverse(tree->right, array);
  array.push_back(tree->value);
}

void preOrderIter(const BST *tree, std::vector<int> &array) {
  std::vector<const BST *> stack = {tree};

  while (!stack.empty()) {
    const BST *curr = stack.back();
    stack.pop_back();
    if (!curr) continue;

    array.push_back(curr->value);
    stack.push_back(curr->right);
    stack.push_back(curr->left);
  }
}
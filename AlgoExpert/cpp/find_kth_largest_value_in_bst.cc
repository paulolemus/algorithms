/* Notes
Difficulty: Medium

k is positive so for k=1, return the largest value in the array, i.e. right most
value. There is guaranteed to be a value to return.

This looks like a reverse in order traversal.
Right->Root->Left.
*/

#include <optional>

// This is an input class. Do not edit.
class BST {
 public:
  int value;
  BST *left = nullptr;
  BST *right = nullptr;

  BST(int value) { this->value = value; }
};

/// Visit BST using reversed In-Order traversal.
/// Returns kth largest value in tree, or none if not found.
std::optional<int> reverseInOrder(BST *curr, const int k, int &kth) {
  if (!curr) return {};

  // Check right side and propagate if found to be kth.
  auto rightOpt = reverseInOrder(curr->right, k, kth);
  if (rightOpt) return rightOpt;

  // Check current node if it is kth.
  if (++kth == k) return {curr->value};

  // Otherwise, return opt from left side.
  return reverseInOrder(curr->left, k, kth);
}

int findKthLargestValueInBst(BST *tree, int k) {
  // Write your code here.
  int kth = 0;
  return reverseInOrder(tree, k, kth).value_or(-1);
}
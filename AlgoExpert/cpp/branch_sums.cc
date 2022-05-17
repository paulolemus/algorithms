/* Notes
Difficulty: Easy
*/

#include <vector>

// This is the class of the input root. Do not edit it.
class BinaryTree {
 public:
  int value;
  BinaryTree *left;
  BinaryTree *right;

  BinaryTree(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
  }
};

/**
 * Arguments:
 * node - Pointer to current node.
 * sum - Sum of branch up to and not including current node.
 * sums - container updated with branch sums.
 */
void dfs(const BinaryTree *node, const int sum, std::vector<int> &sums) {
  if (!node) return;

  const int currSum = node->value + sum;
  if (!node->left && !node->right) {
    sums.push_back(currSum);
    return;
  }

  dfs(node->left, currSum, sums);
  dfs(node->right, currSum, sums);
}

std::vector<int> branchSums(const BinaryTree *root) {
  // Write your code here.
  if (!root) return {};

  std::vector<int> sums;
  dfs(root, 0, sums);
  return sums;
}
/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <vector>

class BinaryTree {
 public:
  int value;
  BinaryTree *left;
  BinaryTree *right;

  BinaryTree(int value);
  void insert(std::vector<int> values, int i = 0);
  void invertedInsert(std::vector<int> values, int i = 0);
};

void invertBinaryTree(BinaryTree *tree) {
  // Write your code here.
  if (tree == nullptr) return;

  std::swap(tree->left, tree->right);
  invertBinaryTree(tree->left);
  invertBinaryTree(tree->right);
}
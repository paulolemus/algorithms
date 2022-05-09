/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <cmath>

// This is an input class. Do not edit.
class BinaryTree {
 public:
  int value;
  BinaryTree *left = nullptr;
  BinaryTree *right = nullptr;

  BinaryTree(int value) { this->value = value; }
};

struct Info {
  bool balanced;
  int height;
};

Info postorder(const BinaryTree *node) {
  if (node == nullptr) return Info{true, 0};

  const Info leftinfo = postorder(node->left);
  if (!leftinfo.balanced) return leftinfo;

  const Info rightinfo = postorder(node->right);
  if (!rightinfo.balanced) return rightinfo;

  if (std::abs(leftinfo.height - rightinfo.height) > 1) return Info{false, 0};

  int height = std::max(leftinfo.height, rightinfo.height) + 1;
  return Info{true, height};
}

bool heightBalancedBinaryTree(const BinaryTree *tree) {
  // Write your code here.
  Info info = postorder(tree);
  return info.balanced;
}
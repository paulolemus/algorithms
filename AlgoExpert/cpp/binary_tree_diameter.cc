/* Notes
Difficulty: Medium

The longest path may or may not go through any particular node.
For any node need to consider 2 things:
height(leftsubtree) + height(rightsubtree) + 1 == longest path through children
and self.
max(height(leftsubtree, hheihgt(rightsubtree))) + 1 == longest path
through 1 of child subtrees, self, and optionally up through parent.

For a node, the longest path can be ether through both of its subtrees and
itself. Height of left subtree + height of right subtree + 1(self).
*/

#include <algorithm>

// This is an input class. Do not edit.
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

struct Path {
  int height{0};
  int diameter{0};
};

/// Recursively discover height of binary tree.
/// Treating height of leaf as 1.
Path dfsHeight(const BinaryTree *curr) {
  // null node has 0 depth.
  if (!curr) return {0, 0};
  const Path leftPath = dfsHeight(curr->left);
  const Path rightPath = dfsHeight(curr->right);

  const int currHeight = std::max(leftPath.height, rightPath.height) + 1;
  const int currDiameter = leftPath.height + rightPath.height;

  const int maxDiameterInSubTree =
      std::max({currDiameter, leftPath.diameter, rightPath.diameter});

  return {currHeight, maxDiameterInSubTree};
}

int binaryTreeDiameter(BinaryTree *tree) {
  // Write your code here.
  Path pathInfo = dfsHeight(tree);
  return pathInfo.diameter;
}
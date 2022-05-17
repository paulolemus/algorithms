/* Notes
Difficulty: Easy
*/

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

int dfsSumDepths(const BinaryTree *curr, const int currDepth) {
  if (!curr) return 0;

  const int leftSum = dfsSumDepths(curr->left, currDepth + 1);
  const int rightSum = dfsSumDepths(curr->right, currDepth + 1);
  return currDepth + leftSum + rightSum;
}

int nodeDepths(const BinaryTree *root) {
  // Write your code here.
  return dfsSumDepths(root, 0);
}
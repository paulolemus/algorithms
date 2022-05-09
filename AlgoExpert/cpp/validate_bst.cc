/* Notes
Difficulty: Medium
*/

#include <limits>

class BST {
 public:
  int value;
  BST *left;
  BST *right;

  BST(int val);
  BST &insert(int val);
};

bool validateRecurse(const BST *curr, const int lower, const int upper) {
  // No node is valid.
  if (!curr) return true;
  const int currVal = curr->value;
  // Return false if this node's value is not within BST range, passed down from
  // parent.
  if (!(lower <= currVal) || !(currVal < upper)) return false;

  // Short circuit recursive fails.
  if (!validateRecurse(curr->left, lower, currVal)) return false;
  if (!validateRecurse(curr->right, currVal, upper)) return false;
  return true;
}

bool validateBst(BST *tree) {
  // Write your code here.
  return validateRecurse(tree, std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max());
}
/* Notes
Difficulty: Easy
*/

#include <cmath>
#include <limits>

class BST {
 public:
  int value;
  BST *left;
  BST *right;

  BST(int val);
  BST &insert(int val);
};

int findClosestValueInBst(const BST *tree, const int target) {
  // Write your code here.
  const BST *curr = tree;
  int minDistance = std::numeric_limits<int>::max();
  int closest = 0;

  while (curr) {
    const int currDistance = std::abs(target - curr->value);
    if (currDistance < minDistance) {
      minDistance = currDistance;
      closest = curr->value;
    }

    // Shortcut closest possible value found.
    if (minDistance <= 0) break;

    if (target < curr->value)
      curr = curr->left;
    else
      curr = curr->right;
  }

  return closest;
}
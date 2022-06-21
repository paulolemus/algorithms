/*
Difficulty: Medium
*/

#include <vector>

class BST {
 public:
  int value;
  BST *left;
  BST *right;

  BST(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
  }

  void insert(int value) {
    if (value < this->value) {
      if (left == nullptr) {
        left = new BST(value);
      } else {
        left->insert(value);
      }
    } else {
      if (right == nullptr) {
        right = new BST(value);
      } else {
        right->insert(value);
      }
    }
  }
};

/// Time: O(n), n = arr.size()
BST *recurseConstruct(const std::vector<int> &arr, const int left,
                      const int right) {
  if (left > right) return nullptr;

  const int mid = (left + right) / 2;
  const int value = arr.at(mid);
  BST *currNode = new BST(value);

  currNode->left = recurseConstruct(arr, left, mid - 1);
  currNode->right = recurseConstruct(arr, mid + 1, right);
  return currNode;
}

/// Time: O(n), Space: O(n), n = array.size()
BST *minHeightBst(std::vector<int> array) {
  // Write your code here.
  if (array.empty()) return nullptr;

  int left = 0;
  int right = static_cast<int>(array.size()) - 1;
  return recurseConstruct(array, left, right);
}
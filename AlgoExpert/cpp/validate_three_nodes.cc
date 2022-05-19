/*
Difficulty: Hard

Provided node pointers are unique + non-nullptr.
Nodes are in same tree.

Solution:
Binary search for either nodeOne or nodeThree as a descendant of nodeTwo.
If one is found, then the other must be an ancestor of nodeTwo.
From the discovered ancestor, binary search until nodeTwo is found or return
false.
*/

// This is an input class. Do not edit.
class BST {
 public:
  int value;
  BST *left = nullptr;
  BST *right = nullptr;

  BST(int value) { this->value = value; }
};

/// Returns true if target node is a descendant of curr node, using binary
/// search.
bool isDescendant(const BST *curr, const BST *const target) {
  if (!curr || !target) return false;

  while (curr && curr != target) {
    if (curr->value <= target->value) {
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }

  return curr == target;
}

/// Time: O(d), d = depth of tree, Space: O(1)
bool validateThreeNodes(const BST *nodeOne, const BST *nodeTwo,
                        const BST *nodeThree) {
  // Write your code here.
  if (!nodeOne || !nodeTwo || !nodeThree) return false;

  // If one of the two nodes is found to be a descendant,
  // the other must be found as ancestor.
  const BST *ancestor = nullptr;
  if (isDescendant(nodeTwo, nodeOne)) {
    ancestor = nodeThree;
  } else if (isDescendant(nodeTwo, nodeThree)) {
    ancestor = nodeOne;
  } else {
    return false;
  }

  return isDescendant(ancestor, nodeTwo);
}
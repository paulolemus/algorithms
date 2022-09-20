/*
Difficulty: Medium
*/

#include <unordered_set>
#include <vector>

class AncestralTree {
 public:
  char name;
  AncestralTree *ancestor;

  AncestralTree(const char name) {
    this->name = name;
    this->ancestor = nullptr;
  }

  void addAsAncestor(std::vector<AncestralTree *> descendants);
};

/// Time: O(d), Space: O(d), d = depth of tree
AncestralTree *getYoungestCommonAncestor(AncestralTree *topAncestor,
                                         AncestralTree *descendantOne,
                                         AncestralTree *descendantTwo) {
  // Write your code here.
  if (!descendantOne) return descendantTwo;
  if (!descendantTwo) return descendantOne;

  // Add all ancestors of one descendant to a set.
  std::unordered_set<const AncestralTree *> seenAncestors;
  AncestralTree *currNode = descendantOne;
  while (currNode) {
    seenAncestors.insert(currNode);
    currNode = currNode->ancestor;
  }

  // The first ancestor found in the set is the YCA.
  currNode = descendantTwo;
  while (currNode) {
    if (seenAncestors.find(currNode) != seenAncestors.cend()) {
      return currNode;
    }
    currNode = currNode->ancestor;
  }

  return topAncestor;
}
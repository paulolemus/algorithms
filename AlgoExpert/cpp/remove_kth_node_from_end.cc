/*
Difficulty: Medium

How to get a pointer to the Kth from end with a single iteration?
Keep two pointers to head.
Move the second one k slots, so k from the start.
The distance between first and second is distance from k to end.
Iterate both until second is at final node, so first is at kth node from end.
*/

#include <vector>

class LinkedList {
 public:
  int value;
  LinkedList *next;

  LinkedList(int value);
  void addMany(std::vector<int> values);
  std::vector<int> getNodesInArray();
};

/// Given head always has at least two nodes and at least k nodes.
/// Time: O(n), Space: O(1)
void removeKthNodeFromEnd(LinkedList *head, const int k) {
  // Write your code here.
  if (!head) return;
  LinkedList *left = head;
  LinkedList *right = head;

  for (int _ = 1; _ < k; ++_) {
    right = right->next;
  }

  LinkedList *prev = nullptr;
  while (right->next) {
    prev = left;
    left = left->next;
    right = right->next;
  }

  LinkedList *next = left->next;
  if (left == head) {
    left->value = next->value;
    left->next = next->next;
    delete next;
  } else {
    prev->next = next;
    delete left;
  }
}
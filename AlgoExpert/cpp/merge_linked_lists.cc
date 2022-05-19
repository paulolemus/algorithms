/*
Difficulty: Hard
*/

// This is an input class. Do not edit.
class LinkedList {
 public:
  int value;
  LinkedList *next;

  LinkedList(int value) {
    this->value = value;
    next = nullptr;
  }
};

/// Time: (m + n), m = headOne length, n = headTwo length, Space: O(1)
LinkedList *mergeLinkedLists(LinkedList *headOne, LinkedList *headTwo) {
  // Write your code here.
  // Guard either as nullptr by returning the other.
  if (!headOne) return headTwo;
  if (!headTwo) return headOne;

  // Store the root node of the merged list as the smaller of the two heads.
  LinkedList *merged = nullptr;
  if (headOne->value <= headTwo->value) {
    merged = headOne;
    headOne = headOne->next;
  } else {
    merged = headTwo;
    headTwo = headTwo->next;
  }

  // HeadOne and Two point to the unmerged portions of the list.
  // curr points to the tail of the merged list.
  // Merge them by appending smaller of unmerged to curr.
  LinkedList *curr = merged;
  while (headOne && headTwo) {
    if (headOne->value < headTwo->value) {
      curr->next = headOne;
      headOne = headOne->next;
    } else {
      curr->next = headTwo;
      headTwo = headTwo->next;
    }
    curr = curr->next;
  }

  curr->next = (headOne) ? headOne : headTwo;
  return merged;
}
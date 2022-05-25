/*
Difficulty: Very Hard
*/

// This is an input struct. Do not edit.
class LinkedList {
 public:
  int value;
  LinkedList *next = nullptr;

  LinkedList(int value) { this->value = value; }
};

/// Time: O(n), Space: O(1)
LinkedList *nodeSwap(LinkedList *head) {
  // Write your code here.
  if (!head) return nullptr;
  LinkedList *newHead = (head->next) ? head->next : head;
  LinkedList *currLeft = head, *currRight = head->next;

  while (currLeft && currRight) {
    // Store next adjacent pair.
    LinkedList *nextLeft = currRight->next;
    LinkedList *nextRight = (nextLeft) ? nextLeft->next : nullptr;

    currRight->next = currLeft;
    currLeft->next = (nextRight) ? nextRight : nextLeft;

    currLeft = nextLeft;
    currRight = nextRight;
  }

  return newHead;
}
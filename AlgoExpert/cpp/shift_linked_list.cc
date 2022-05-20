/*
Difficulty: Hard
*/

class LinkedList {
 public:
  int value;
  LinkedList *next;

  LinkedList(int value) {
    this->value = value;
    next = nullptr;
  }
};

/// Time: O(n), Space: O(1)
LinkedList *shiftLinkedList(LinkedList *head, int k) {
  // Write your code here.
  if (!head) return head;

  // Find tail node and length of list.
  LinkedList *tail = head;
  int size = 1;
  while (tail && tail->next) {
    tail = tail->next;
    size++;
  }

  // Convert k from negative to equivalent positive and
  // reduce excess rotations.
  k = (k % size + size) % size;
  if (k <= 0 || size <= 1) return head;

  // Make list circular.
  // Navigate to the new head, then set the node before the new head as the new
  // tail.
  tail->next = head;
  LinkedList *curr = head;
  LinkedList *prev = nullptr;
  for (int _ = 0; _ < size - k; ++_) {
    prev = curr;
    curr = curr->next;
  }
  if (prev) prev->next = nullptr;

  return curr;
}
/*
Difficulty: Easy
*/

// This is an input struct. Do not edit.
class LinkedList {
 public:
  int value;
  LinkedList *next = nullptr;

  LinkedList(int value) { this->value = value; }
};

/// Time: O(n), Space: O(1)
LinkedList *removeDuplicatesFromLinkedList(LinkedList *linkedList) {
  LinkedList *curr = linkedList;
  while (curr && curr->next) {
    if (curr->value == curr->next->value) {
      curr->next = curr->next->next;
    } else {
      curr = curr->next;
    }
  }

  return linkedList;
}
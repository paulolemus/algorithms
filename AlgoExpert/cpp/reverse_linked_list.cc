/*
Difficulty: Hard
*/

class LinkedList {
 public:
  int value;
  LinkedList *next;

  LinkedList(int value) {
    this->value = value;
    this->next = nullptr;
  }
};

LinkedList *reverseLinkedList(LinkedList *head) {
  // Write your code here.
  LinkedList *prev = nullptr, *curr = head;

  while (curr) {
    LinkedList *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}
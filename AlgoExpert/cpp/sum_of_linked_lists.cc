/*
Difficulty: Medium

Function must create and return a new LinkedList.
*/

// This is an input struct. Do not edit.
class LinkedList {
 public:
  int value;
  LinkedList *next = nullptr;

  LinkedList(const int value) { this->value = value; }
};

LinkedList *deepCopyLinkedList(const LinkedList *list) {
  if (!list) return nullptr;

  LinkedList *head = new LinkedList(list->value);
  LinkedList *tail = head;
  list = list->next;
  while (list) {
    tail->next = new LinkedList(list->value);
    tail = tail->next;
    list = list->next;
  }
  return head;
}

/// Time: O(max(l, r)), Space: O(max(l, r))
/// l = length of listOne, r = length of listTwo
LinkedList *sumOfLinkedLists(const LinkedList *linkedListOne,
                             const LinkedList *linkedListTwo) {
  // Write your code here.
  if (!linkedListOne) return deepCopyLinkedList(linkedListTwo);
  if (!linkedListTwo) return deepCopyLinkedList(linkedListOne);

  LinkedList *head = nullptr;
  LinkedList *curr = nullptr;
  const LinkedList *left = linkedListOne;
  const LinkedList *right = linkedListTwo;
  bool carry = false;

  for (; left && right; left = left->next, right = right->next) {
    int value = left->value + right->value + static_cast<int>(carry);
    carry = value >= 10;
    if (carry) {
      value -= 10;
    }

    LinkedList *newNode = new LinkedList(value);
    if (!head) head = newNode;
    if (!curr) {
      curr = newNode;
    } else {
      curr->next = newNode;
      curr = newNode;
    }
  }

  // Propagate carry through any remaining list.
  const LinkedList *remaining = (left) ? left : right;
  for (; remaining; remaining = remaining->next) {
    int value = remaining->value + static_cast<int>(carry);
    carry = value >= 10;
    if (carry) {
      value -= 10;
    }
    curr->next = new LinkedList(value);
    curr = curr->next;
  }

  if (carry) {
    curr->next = new LinkedList(1);
  }

  return head;
}
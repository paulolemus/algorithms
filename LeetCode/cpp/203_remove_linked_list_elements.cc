/*
Difficulty: Easy
*/

// Provided definition.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  /// Time: O(n), Space: O(1)
  ListNode* removeElements(ListNode* head, const int val) {
    // Move to first node in list without val.
    while (head && head->val == val) {
      head = head->next;
    }

    if (!head) return nullptr;

    // Iterate list from new head removing all instances of val.
    // Not specified in problem on how to handle removed nodes.
    ListNode* prev = head;
    ListNode* curr = head->next;
    while (curr) {
      if (curr->val == val) {
        prev->next = curr->next;
      } else {
        prev = curr;
      }
      curr = curr->next;
    }

    return head;
  }
};
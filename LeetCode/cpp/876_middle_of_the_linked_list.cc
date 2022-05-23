/*
Difficulty: Easy
Runtime: 0 ms (100%)
*/

/// Definition for singly-linked list.
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
  /// n = length of list.
  ListNode* middleNode(ListNode* head) {
    if (!head) return nullptr;

    ListNode* middle = head;
    const ListNode* end = head;
    while (end && end->next) {
      middle = middle->next;
      end = end->next->next;
    }

    return middle;
  }
};
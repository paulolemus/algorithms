"""
Difficulty: Very Hard
"""

# This is an input class. Do not edit.
class LinkedList:
    def __init__(self, value):
        self.value = value
        self.next = None


def nodeSwap(head):
    # Write your code here.
    left_node = head
    right_node = head.next

    # Base case, list of length 1 has no change.
    if not right_node:
        return head

    new_head = right_node

    while left_node and right_node:
        # Get the next pair, either (Some, Some), (Some, None), or (None, None)
        next_left_node = right_node.next
        next_right_node = next_left_node and next_left_node.next

        # Update current pair pointers
        right_node.next = left_node
        left_node.next = next_right_node or next_left_node

        # Shift over current pair
        left_node = next_left_node
        right_node = next_right_node

    return new_head

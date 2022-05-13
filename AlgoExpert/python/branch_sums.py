"""
Difficulty: Easy
"""

from typing import List, Optional

# This is the class of the input root. Do not edit it.
class BinaryTree:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def dfs(node: Optional[BinaryTree], total: int, sums: list):
    if not node:
        return

    new_total = total + node.value
    if not node.left and not node.right:
        sums.append(new_total)
        return

    dfs(node.left, new_total, sums)
    dfs(node.right, new_total, sums)


def branchSums(root: Optional[BinaryTree]) -> List[int]:
    # Write your code here.
    sums = []
    dfs(root, 0, sums)
    return sums

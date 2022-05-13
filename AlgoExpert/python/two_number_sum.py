"""
Difficulty: Easy
"""

from typing import List


def twoNumberSum(array: List[int], targetSum: int) -> List[int]:
    # Write your code here.
    pairs = set()

    for num in array:
        if num in pairs:
            return [num, targetSum - num]
        pairs.add(targetSum - num)

    return []

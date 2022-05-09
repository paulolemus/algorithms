"""
Difficulty: Easy
"""


def twoNumberSum(array, targetSum):
    # Write your code here.
    pairs = set()

    for num in array:
        if num in pairs:
            return [num, targetSum - num]
        pairs.add(targetSum - num)

    return []

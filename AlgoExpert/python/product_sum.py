"""
Difficulty: Easy
"""


def recurseProductSum(array, depth: int = 1) -> int:
    curr_sum = 0
    for item in array:
        if type(item) == list:
            curr_sum += recurseProductSum(item, depth + 1)
        else:
            curr_sum += item

    return curr_sum * depth


# Tip: You can use the type(element) function to check whether an item
# is a list or an integer.
# Time: O(n), Space: O(d), n = number of ints in array, d = greatest depth
def productSum(array):
    # Write your code here.
    return recurseProductSum(array)

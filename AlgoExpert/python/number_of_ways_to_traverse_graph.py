"""
Difficulty: Medium
"""

from math import factorial


def numberOfWaysToTraverseGraph(width, height):
    # Write your code here.
    rights = width - 1
    downs = height - 1
    return factorial(rights + downs) / (factorial(rights) * factorial(downs))

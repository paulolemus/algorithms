"""
Difficulty: Easy
"""

from typing import List


def tandemBicycle(
    redShirtSpeeds: List[int], blueShirtSpeeds: List[int], fastest: bool
) -> int:
    # Write your code here.
    redShirtSpeeds.sort()
    if fastest:
        blueShirtSpeeds.sort(reverse=True)
    else:
        blueShirtSpeeds.sort()

    total_speed = 0
    for red, blue in zip(redShirtSpeeds, blueShirtSpeeds):
        total_speed += max(red, blue)

    return total_speed

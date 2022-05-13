"""
Difficulty: Easy
"""


def tandemBicycle(redShirtSpeeds, blueShirtSpeeds, fastest):
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

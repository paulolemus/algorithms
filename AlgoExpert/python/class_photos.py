"""
Difficulty: Easy
"""


def classPhotos(redShirtHeights, blueShirtHeights):
    # Write your code here.
    redShirtHeights.sort()
    blueShirtHeights.sort()
    red_taller = 0
    blue_taller = 0

    for red, blue in zip(redShirtHeights, blueShirtHeights):
        if red > blue:
            red_taller += 1
        elif blue > red:
            blue_taller += 1
        else:
            return False
        if red_taller and blue_taller:
            return False

    return True

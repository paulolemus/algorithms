"""
Difficulty: Easy
"""

from collections import Counter


def generateDocument(characters: str, document: str) -> bool:
    # Write your code here.
    chars_count = Counter(characters)
    document_count = Counter(document)

    for key, value in document_count.items():
        if key not in chars_count or chars_count[key] < value:
            return False
    return True

"""
Difficulty: Easy
"""


def minHeapifyThree(heap):
    """Given a binary heap of size 3, ensure root has smallest value."""
    smallest = 0
    left = 1
    right = 2

    if heap[left] < heap[smallest]:
        smallest = left
    if heap[right] < heap[smallest]:
        smallest = right
    heap[smallest], heap[0] = heap[0], heap[smallest]


# Time: O(n), heap, minHeapifyTree and sort are O(1) as fixed small size.
def findThreeLargestNumbers(array):
    # Write your code here.
    heap = [-float("inf")] * 3

    for num in array:
        if num > heap[0]:
            heap[0] = num
            minHeapifyThree(heap)

    heap.sort()
    return heap

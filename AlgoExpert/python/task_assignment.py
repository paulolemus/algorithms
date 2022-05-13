"""
Difficulty: Medium
"""

from typing import List


def taskAssignment(k: int, tasks: List[int]) -> List[List[int]]:
    # Write your code here.
    task_indices = [(task, idx) for idx, task in enumerate(tasks)]
    task_indices.sort(key=lambda n: n[0])

    assignments = k * [None]
    size = len(tasks)
    for idx in range(size // 2):
        assignments[idx] = [task_indices[idx][1], task_indices[size - 1 - idx][1]]

    return assignments

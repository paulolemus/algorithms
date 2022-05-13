"""
Difficulty: Easy
"""

from typing import List

# O(nlogn + n) time, O(1) space
def minimumWaitingTime(queries: List[int]) -> int:
    # Write your code here.
    if len(queries) == 1:
        return 0
    queries.sort()

    total_waiting_time = 0
    last_waiting_time = 0
    last_duration = 0

    for query in queries:
        last_waiting_time += last_duration
        total_waiting_time += last_waiting_time
        last_duration = query

    return total_waiting_time

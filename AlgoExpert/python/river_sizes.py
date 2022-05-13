"""
Difficulty: Medium
"""

from dataclasses import dataclass
from typing import List

_LAND = 0
_RIVER = 1


@dataclass(frozen=True, eq=True, order=False)
class Pos:
    r: int  # Row
    c: int  # Column


def adjacentPos(pos: Pos, rows: int, cols: int) -> List[Pos]:
    """Returns all adjacent Pos of the given pos.
    Returned Pos are guaranteed to be within bounds, on either land or river.
    """
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    adj = []

    for r_dir, c_dir in directions:
        new_pos = Pos(pos.r + r_dir, pos.c + c_dir)
        if 0 <= new_pos.r < rows and 0 <= new_pos.c < cols:
            adj.append(new_pos)

    return adj


def flood(pos: Pos, matrix: List[List[int]]) -> int:
    """Returns the size of the river that includes pos.
    Args:
            pos - position in matrix that contains a river.
            matrix - mutable matrix of land/river.
    Returns:
            int representing size of river.
    """
    rows, cols = len(matrix), len(matrix[0])
    matrix[pos.r][pos.c] = _LAND
    river_positions = [pos]
    river_size = 0

    while river_positions:
        curr_pos = river_positions.pop()
        river_size += 1

        for adj_pos in adjacentPos(curr_pos, rows, cols):
            if matrix[adj_pos.r][adj_pos.c] == _RIVER:
                matrix[adj_pos.r][adj_pos.c] = _LAND
                river_positions.append(adj_pos)

    return river_size


def riverSizes(matrix: List[List[int]]) -> List[int]:
    # Write your code here.
    # Guard empty grid.
    if len(matrix) == 0 or len(matrix[0]) == 0:
        return []

    rows, cols = len(matrix), len(matrix[0])
    river_sizes = []

    for row in range(rows):
        for col in range(cols):
            if matrix[row][col] == _RIVER:
                river_sizes.append(flood(Pos(row, col), matrix))

    return river_sizes

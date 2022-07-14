/*
Difficulty: Medium
*/

#include <vector>

std::vector<int> searchInSortedMatrix(
    const std::vector<std::vector<int>> matrix, const int target) {
  // Write your code here.
  if (matrix.empty() || matrix[0].empty()) return {-1, -1};

  int row = 0, col = matrix[0].size() - 1;
  while (row < matrix.size() && col >= 0) {
    const int value = matrix[row][col];

    if (value == target) {
      return {row, col};
    } else if (target < value) {
      col--;
    } else {
      row++;
    }
  }

  return {-1, -1};
}

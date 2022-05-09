/* Notes
Difficulty: Medium

Iteration order:
1. row = lower, col = lower->upper
2. row = lower+1->upper, col = upper
3. row = upper, col = upper-1->lower
4. row = upper-1->lower+1, col = lower
*/

#include <vector>

/// Given the bounds of a rectangle inclusive, navigate its perimeter and add
/// all values to the output array.
void traverseRectangle(const std::vector<std::vector<int>>& array,
                       const int lowerRow, const int upperRow,
                       const int lowerCol, const int upperCol,
                       std::vector<int>& output) {
  for (int row = lowerRow, col = lowerCol; col <= upperCol; ++col) {
    output.push_back(array[row][col]);
  }
  for (int row = lowerRow + 1, col = upperCol; row <= upperRow; ++row) {
    output.push_back(array[row][col]);
  }
  for (int row = upperRow, col = upperCol - 1; col >= lowerCol; --col) {
    if (row == lowerRow) break;
    output.push_back(array[row][col]);
  }
  for (int row = upperRow - 1, col = lowerCol; row >= lowerRow + 1; --row) {
    if (col == upperCol) break;
    output.push_back(array[row][col]);
  }
}

std::vector<int> spiralTraverse(std::vector<std::vector<int>> array) {
  // Write your code here.
  std::vector<int> unrolled;

  // Guard.
  if (array.empty() || array[0].empty()) return unrolled;

  const int rows = array.size();
  const int cols = array[0].size();
  int lowerRow = 0, upperRow = rows - 1;
  int lowerCol = 0, upperCol = cols - 1;

  unrolled.reserve(rows * cols);

  while (lowerRow <= upperRow && lowerCol <= upperCol) {
    traverseRectangle(array, lowerRow, upperRow, lowerCol, upperCol, unrolled);
    lowerRow++;
    upperRow--;
    lowerCol++;
    upperCol--;
  }

  return unrolled;
}
/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <vector>

/// Given an array, a target and a current index,
/// return the next index where array[index] != target.
int seekNonTarget(const std::vector<int>& array, const int target, int idx) {
  while (idx < array.size() && array[idx] == target) idx++;
  return idx;
}

std::vector<int> threeNumberSort(std::vector<int> array,
                                 std::vector<int> order) {
  // Write your code here.
  if (array.size() <= 1) return array;

  int idxUnsorted = 0;
  // Outer for loop contributes O(1) time, order fixed size of 3.
  for (const int target : order) {
    idxUnsorted = seekNonTarget(array, target, idxUnsorted);

    for (int i = array.size() - 1; idxUnsorted < i; --i) {
      if (array[i] == target) {
        std::swap(array[i], array[idxUnsorted]);
        idxUnsorted = seekNonTarget(array, target, idxUnsorted + 1);
      }
    }
  }

  return array;
}
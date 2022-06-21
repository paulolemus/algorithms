/*
Difficulty: Hard
*/

#include <cstddef>
#include <vector>

/// Given valid indices inclusive left and right for array, sort array using
/// quicksort.
void quickSortRecurse(std::vector<int>& array, const std::size_t leftBound,
                      const std::size_t rightBound) {
  // Guard invalid boundaries.
  if (leftBound >= rightBound) return;
  if (leftBound >= array.size() || rightBound >= array.size()) return;

  // Use the midpoint as pivot to avoid worst case complexity for sorted arrays.
  // Pull the selected pivot to the front.
  const std::size_t midIdx = (leftBound + rightBound) / 2;
  std::swap(array[midIdx], array[leftBound]);

  std::size_t pivotIdx = leftBound, left = leftBound + 1, right = rightBound;
  const int pivot = array[pivotIdx];

  while (left <= right) {
    if (array[left] > pivot && array[right] < pivot) {
      std::swap(array[left], array[right]);
      left++;
      right--;
    } else {
      if (array[left] <= pivot) left++;
      if (array[right] >= pivot) right--;
    }
  }
  std::swap(array[pivotIdx], array[right]);
  quickSortRecurse(array, leftBound, right - 1);
  quickSortRecurse(array, right + 1, rightBound);
}

std::vector<int> quickSort(std::vector<int> array) {
  // Write your code here.
  if (array.size() <= 1) return array;
  quickSortRecurse(array, 0, array.size() - 1);
  return array;
}
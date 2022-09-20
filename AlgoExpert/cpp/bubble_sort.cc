/*
Difficulty: Easy
*/

#include <algorithm>
#include <cstddef>
#include <vector>

/// Time: O(n^2), Space: O(1)
std::vector<int> bubbleSort(std::vector<int> array) {
  // Write your code here.
  if (array.size() <= 1) return array;

  std::size_t maxIdx = array.size() - 1;
  bool swapped = false;
  do {
    swapped = false;
    for (std::size_t i = 0; i < maxIdx; ++i) {
      if (array[i] > array[i + 1]) {
        std::swap(array[i], array[i + 1]);
        swapped = true;
      }
    }
    // Each loop the final item of the unsorted array ends in
    // its final position and doesn't need to be further checked.
    maxIdx--;
  } while (swapped);

  return array;
}
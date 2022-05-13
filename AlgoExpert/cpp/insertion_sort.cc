/* Notes
Difficulty: Easy
*/

#include <algorithm>
#include <vector>

std::vector<int> insertionSort(std::vector<int> array) {
  // Write your code here.
  const int size = array.size();

  for (int idx = 1; idx < size; ++idx) {
    for (int curr = idx; curr > 0 && array[curr] < array[curr - 1]; --curr) {
      std::swap(array[curr], array[curr - 1]);
    }
  }
  return array;
}
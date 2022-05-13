/* Notes
Difficulty: Easy
*/

#include <vector>

std::vector<int> selectionSort(std::vector<int> array) {
  // Write your code here.
  const int size = array.size();

  for (int idxUnsorted = 0; idxUnsorted < size - 1; ++idxUnsorted) {
    int idxSmallest = idxUnsorted;

    // Search for a smaller value in unsorted portion of array.
    for (int curr = idxUnsorted + 1; curr < size; ++curr) {
      if (array[curr] < array[idxSmallest]) idxSmallest = curr;
    }
    std::swap(array[idxUnsorted], array[idxSmallest]);
  }

  return array;
}
/* Notes
Difficulty: Easy
*/

#include <vector>

int binarySearch(const std::vector<int> array, const int target) {
  // Write your code here.
  int left = 0;
  int right = array.size() - 1;

  while (left <= right) {
    const int mid = (left + right) / 2;
    const int value = array[mid];

    if (target == value) {
      return mid;
    } else if (target > value) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}
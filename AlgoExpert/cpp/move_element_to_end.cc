/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <vector>

/**
 * time: O(n), n = array.size()
 * space: O(1)
 */
std::vector<int> moveElementToEnd(std::vector<int> array, const int toMove) {
  // Write your code here.
  int head = 0, tail = array.size() - 1;

  while (head < tail && array[tail] == toMove) tail--;

  while (head < tail) {
    if (array[head] == toMove) {
      std::swap(array[head], array[tail]);
      head++;
      tail--;
      while (head < tail && array[tail] == toMove) tail--;
    } else {
      head++;
    }
  }

  return array;
}

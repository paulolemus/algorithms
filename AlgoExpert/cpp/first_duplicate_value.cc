/* Notes
Difficulty: Medium

All values given are positive.
Allowed to mutate input array.
*/

#include <cmath>
#include <unordered_set>
#include <vector>

/// Time: O(n), Space: O(1) uses existing array.
int firstDuplicateValue(std::vector<int> array) {
  // Each value in array can be perfectly mapped to an index (value - 1).
  // Instead of using a set to record seen values,
  // negate the number in the value's index.
  for (int num : array) {
    num = std::abs(num);
    const int idx = num - 1;

    if (array[idx] < 0) {
      return num;
    }
    array[idx] *= -1;
  }

  return -1;
}

/// Time: O(n), Space: O(n).
int firstDuplicateValueAlt(std::vector<int> array) {
  std::unordered_set<int> seen;

  for (const int num : array) {
    if (seen.find(num) != seen.end()) {
      return num;
    } else {
      seen.insert(num);
    }
  }

  return -1;
}
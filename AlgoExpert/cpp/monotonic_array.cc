/* Notes
Difficulty: Medium

Can have equal numbers.
Array of all increasing elements is monotonic, because they are entirely
non-decreasing. Cannot check first n, because they can be all equal, which
provides no info about what should follow.

Naive solution:
All arrays of size <= 2 are monotonic.
keep two bools, increased & decreased as false.
Iterate array.
for each number, compare it to the last number.

Time: O(n)
space: O(1)
*/

#include <vector>

bool isMonotonic(const std::vector<int> array) {
  // Write your code here.
  if (array.size() <= 2) return true;

  bool increasing = false, decreasing = false;
  int lastNum = array[0];

  for (const int num : array) {
    if (num > lastNum) {
      increasing = true;
    } else if (num < lastNum) {
      decreasing = true;
    }
    lastNum = num;

    if (increasing && decreasing) return false;
  }

  return true;
}
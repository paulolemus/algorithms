/* Notes
Difficulty: Easy
*/

#include <cmath>
#include <vector>

std::vector<int> sortedSquaredArray(const std::vector<int> array) {
  // Write your code here.
  if (array.empty()) return {};

  std::vector<int> squared(array.size(), 0);
  int l = 0, r = array.size() - 1;

  // Fill squared from back to front.
  for (int out = squared.size() - 1; out >= 0; --out) {
    const int labs = std::abs(array[l]);
    const int rabs = std::abs(array[r]);

    if (labs < rabs) {
      squared[out] = rabs * rabs;
      r--;
    } else {
      squared[out] = labs * labs;
      l++;
    }
  }

  return squared;
}
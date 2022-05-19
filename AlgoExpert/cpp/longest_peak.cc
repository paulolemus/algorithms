/*
Difficulty: Medium
*/

#include <algorithm>
#include <vector>

/// Returns length of peak with idxPeak as the index of the tallest point.
int findPeakLength(const std::vector<int>& array, const int idxPeak) {
  int length = 1;
  for (int i = idxPeak + 1; i < array.size() && array[i] < array[i - 1]; ++i) {
    length++;
  }
  for (int i = idxPeak - 1; i >= 0 && array[i] < array[i + 1]; --i) {
    length++;
  }
  return length;
}

/// Time: O(n), Space: O(1)
int longestPeak(const std::vector<int> array) {
  // Write your code here.
  int longest = 0;

  // Guaranteed to have valid index for i - 1, i + 1.
  // In worst case, findPeakLength as inner loop results in Time: O(2n) -> O(n).
  for (int i = 1; i < static_cast<int>(array.size()) - 1; ++i) {
    const int mid = array[i];
    const int left = array[i - 1];
    const int right = array[i + 1];
    if (mid > left && mid > right) {
      longest = std::max(longest, findPeakLength(array, i));
    }
  }

  return longest;
}
/*
Difficulty: Medium
*/

#include <algorithm>
#include <vector>

/// Time: O(n), Space: O(1)
int kadanesAlgorithm(const std::vector<int> array) {
  // Write your code here.
  if (array.empty()) return 0;

  int currIndexMaxSum = array[0];
  int maxSum = array[0];
  for (std::vector<int>::size_type i = 1; i < array.size(); ++i) {
    const int currValue = array[i];
    currIndexMaxSum = std::max(currValue, currValue + currIndexMaxSum);
    maxSum = std::max(maxSum, currIndexMaxSum);
  }

  return maxSum;
}
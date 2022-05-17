/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <vector>

int maxSubsetSumNoAdjacent(std::vector<int> array) {
  // Write your code here.
  if (array.empty()) return 0;

  for (int i = 0; i < array.size(); ++i) {
    const int currValue = array[i];
    const int prevMaxSum = (i >= 1) ? array[i - 1] : 0;
    const int nonAdjSum = (i >= 2) ? array[i - 2] : 0;
    const int currMaxSum = std::max(currValue + nonAdjSum, prevMaxSum);
    array[i] = currMaxSum;
  }

  return array.back();
}
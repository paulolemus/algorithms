/* Notes
Difficulty: Easy
*/

#include <unordered_set>
#include <vector>

std::vector<int> twoNumberSum(const std::vector<int> array,
                              const int targetSum) {
  // Write your code here.
  std::unordered_set<int> pairs;

  for (const int num : array) {
    if (pairs.find(num) != pairs.end()) {
      return {num, targetSum - num};
    }
    pairs.insert(targetSum - num);
  }
  return {};
}
/*
Difficulty: Hard
*/

#include <unordered_set>
#include <vector>

struct Range {
  int start{0};
  int end{0};
  int size() const { return this->end - this->start + 1; }
};

/// Time: O(n), Space: O(n)
std::vector<int> largestRange(const std::vector<int> array) {
  // Write your code here.
  if (array.empty()) return {};

  std::unordered_set<int> values(array.cbegin(), array.cend());
  std::unordered_set<int> visited;
  visited.reserve(values.size());

  Range maxRange{array[0], array[0]};
  for (const int num : array) {
    if (visited.find(num) != visited.cend()) {
      continue;
    }

    Range currRange{num, num};
    for (int right = num; values.find(right) != values.cend(); ++right) {
      visited.insert(right);
      currRange.end = right;
    }
    for (int left = num - 1; values.find(left) != values.cend(); --left) {
      visited.insert(left);
      currRange.start = left;
    }

    if (currRange.size() > maxRange.size()) {
      maxRange = currRange;
    }
  }

  return {maxRange.start, maxRange.end};
}
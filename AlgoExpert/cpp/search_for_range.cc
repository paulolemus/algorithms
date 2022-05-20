/*
Difficulty: Hard
*/

#include <algorithm>
#include <optional>
#include <vector>

struct Range {
  int start{0};
  int end{0};
  int i{0};
};

/// If target is found in array, returns a range with i as the index of the
/// target in array. Included in range is the start and end inclusive of
/// smallest range in which i was found.
std::optional<Range> binarySearch(const std::vector<int>& array,
                                  const int target, int left, int right) {
  if (left < 0 || right >= array.size()) return {};

  while (left <= right) {
    const int mid = (left + right) / 2;
    if (array[mid] == target) {
      return Range{left, right, mid};
    } else if (array[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return {};
}

/// Binary search for the smallest index in array where array[index] == target.
/// Assumes target exists in range left..=right.
int findLowestTargetIndex(const std::vector<int>& array, const int target,
                          int left, int right) {
  int lowestIdx = right;
  auto rangeOpt = binarySearch(array, target, left, right);
  while (rangeOpt) {
    lowestIdx = rangeOpt->i;
    rangeOpt = binarySearch(array, target, rangeOpt->start, rangeOpt->i - 1);
  }
  return lowestIdx;
}

/// Binary search for the largest index where array[index] == target.
/// Assumes target exists in range left..=right.
int findHighestTargetIndex(const std::vector<int>& array, const int target,
                           int left, int right) {
  int highestIdx = left;
  auto rangeOpt = binarySearch(array, target, left, right);
  while (rangeOpt) {
    highestIdx = rangeOpt->i;
    rangeOpt = binarySearch(array, target, rangeOpt->i + 1, rangeOpt->end);
  }
  return highestIdx;
}

/// Time: O(log n), n = array.size(), Space: O(1)
std::vector<int> searchForRange(const std::vector<int> array,
                                const int target) {
  // Write your code here.
  if (array.empty()) return {-1, -1};

  // Step 1. Binary search for any instance of target.
  std::optional<Range> rangeOpt =
      binarySearch(array, target, 0, array.size() - 1);
  if (!rangeOpt) return {-1, -1};

  // The range contains the upper and lower bounds inclusive for the range
  // solution. Step 2. Find lower and upper of solution range within first
  // binary search range.
  return {findLowestTargetIndex(array, target, rangeOpt->start, rangeOpt->i),
          findHighestTargetIndex(array, target, rangeOpt->i, rangeOpt->end)};
}

/// Alternative STL solution.
/// Time: O(log n), Space: O(1)
std::vector<int> searchForRangeStl(const std::vector<int> array,
                                   const int target) {
  // Write your code here.
  if (array.empty()) return {-1, -1};
  auto lower = std::lower_bound(array.cbegin(), array.cend(), target);
  auto upper = std::upper_bound(array.cbegin(), array.cend(), target);
  // Bound checks.
  if (lower >= array.cend() || upper <= array.cbegin()) return {-1, -1};
  // Upper points to first greater than target,
  // so last target index is 1 position behind upper.
  upper--;
  // Target checks.
  if (*lower != target || *upper != target) return {-1, -1};

  return {
      static_cast<int>(lower - array.cbegin()),
      static_cast<int>(upper - array.cbegin()),
  };
}
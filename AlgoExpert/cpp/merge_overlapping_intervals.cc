/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <utility>
#include <vector>

/// Returns true if the two intervals are overlapped.
/// UB is vectors are not both of size 2.
bool isOverlapping(const std::vector<int>& left,
                   const std::vector<int>& right) {
  const int leftLower = left[0], rightLower = right[0];
  const int leftUpper = left[1], rightUpper = right[1];
  return rightLower <= leftUpper && leftLower <= rightUpper;
}

/// Returns a new interval that contains both intervals.
/// This assumes the intervals are overlapping.
std::vector<int> mergeOverlapping(const std::vector<int>& left,
                                  const std::vector<int>& right) {
  const int lower = std::min(left[0], right[0]);
  const int upper = std::max(left[1], right[1]);
  return {lower, upper};
}

/// Compares two intervals by their lower bound.
bool cmpIntervalsByLower(const std::vector<int>& left,
                         const std::vector<int>& right) {
  return left[0] < right[0];
}

std::vector<std::vector<int>> mergeOverlappingIntervals(
    std::vector<std::vector<int>> intervals) {
  // Write your code here.
  // Guard small / empty.
  if (intervals.size() <= 1) return intervals;

  std::vector<std::vector<int>> merged;
  // Sort all intervals by their lower bound.
  std::sort(intervals.begin(), intervals.end(), cmpIntervalsByLower);

  std::vector<int> curr = intervals[0];
  for (const auto& interval : intervals) {
    if (isOverlapping(curr, interval)) {
      curr = mergeOverlapping(curr, interval);
    } else {
      merged.push_back(std::move(curr));
      curr = interval;
    }
  }
  merged.push_back(std::move(curr));

  return merged;
}